#include <iostream>
#include <memory>
#include <vector>
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Matrix3.h"
#include "Physics/RigidBody.h"
#include "Physics/PhysicsWorld.h"
#include "Collision/CollisionPrimitive.h"
#include "UnrealIntegration/UnrealPhysicsBridge.h"

using namespace std;

// Example physics simulation
class PhysicsExample {
public:
    PhysicsWorld world;
    vector<unique_ptr<RigidBody>> bodies;
    vector<unique_ptr<CollisionPrimitive>> primitives;
    
    PhysicsExample() : world(100, 10) {
        // Set up physics world
        world.setGravity(Vector3(0, -9.81f, 0));
        world.setDamping(0.99f);
        
        // Create ground plane
        createGround();
        
        // Create some test objects
        createTestObjects();
        
        // Add force generators
        setupForceGenerators();
    }
    
    void createGround() {
        // Create a static ground plane
        auto groundBody = make_unique<RigidBody>();
        groundBody->setInfiniteMass(); // Static body
        groundBody->setPosition(Vector3(0, -1, 0));
        
        auto groundBox = make_unique<CollisionBox>(Vector3(10, 0.5f, 10));
        groundBox->body = groundBody.get();
        
        bodies.push_back(move(groundBody));
        primitives.push_back(groundBox.get());
        world.addPrimitive(groundBox.release());
    }
    
    void createTestObjects() {
        // Create a falling sphere
        auto sphereBody = make_unique<RigidBody>();
        sphereBody->setMass(1.0f);
        sphereBody->setInertiaTensor(RigidBody::calculateSphereInertiaTensor(1.0f, 0.5f));
        sphereBody->setPosition(Vector3(0, 5, 0));
        sphereBody->setLinearVelocity(Vector3(2, 0, 0));
        
        auto spherePrimitive = make_unique<CollisionSphere>(0.5f);
        spherePrimitive->body = sphereBody.get();
        
        bodies.push_back(move(sphereBody));
        primitives.push_back(spherePrimitive.get());
        world.addPrimitive(spherePrimitive.release());
        
        // Create a falling box
        auto boxBody = make_unique<RigidBody>();
        boxBody->setMass(2.0f);
        boxBody->setInertiaTensor(RigidBody::calculateBoxInertiaTensor(2.0f, 1.0f, 1.0f, 1.0f));
        boxBody->setPosition(Vector3(3, 8, 0));
        boxBody->setAngularVelocity(Vector3(0, 0, 1));
        
        auto boxPrimitive = make_unique<CollisionBox>(Vector3(0.5f, 0.5f, 0.5f));
        boxPrimitive->body = boxBody.get();
        
        bodies.push_back(move(boxBody));
        primitives.push_back(boxPrimitive.get());
        world.addPrimitive(boxPrimitive.release());
    }
    
    void setupForceGenerators() {
        // Add gravity to all bodies
        auto gravity = make_unique<PhysicsWorld::Gravity>(Vector3(0, -9.81f, 0));
        for (auto& body : bodies) {
            if (body->hasFiniteMass()) {
                world.addForceGenerator(body.get(), gravity.get());
            }
        }
    }
    
    void runSimulation(float duration) {
        cout << "Running physics simulation for " << duration << " seconds..." << endl;
        
        float timeStep = 1.0f / 60.0f; // 60 FPS
        float currentTime = 0.0f;
        
        while (currentTime < duration) {
            // Run physics step
            world.runPhysics(timeStep);
            
            // Print object positions every second
            if (static_cast<int>(currentTime) != static_cast<int>(currentTime - timeStep)) {
                printObjectStates();
            }
            
            currentTime += timeStep;
        }
        
        cout << "Simulation complete!" << endl;
    }
    
    void printObjectStates() {
        cout << "\n--- Object States ---" << endl;
        for (size_t i = 0; i < bodies.size(); ++i) {
            Vector3 pos = bodies[i]->getPosition();
            Vector3 vel = bodies[i]->getLinearVelocity();
            cout << "Object " << i << ": Pos(" << pos.x << ", " << pos.y << ", " << pos.z 
                 << ") Vel(" << vel.x << ", " << vel.y << ", " << vel.z << ")" << endl;
        }
        cout << "Contacts: " << world.getContacts().size() << endl;
    }
    
    void demonstrateUnrealIntegration() {
        cout << "\n--- Unreal Engine Integration Demo ---" << endl;
        
        // This would normally work with actual Unreal Engine objects
        // For demo purposes, we'll show the conversion functions
        
        Vector3 physicsPos(1.0f, 2.0f, 3.0f);
        Quaternion physicsRot = Quaternion::fromEulerAngles(0.5f, 1.0f, 0.0f);
        
        cout << "Physics Position: " << physicsPos << endl;
        cout << "Physics Rotation: (" << physicsRot.w << ", " << physicsRot.x 
             << ", " << physicsRot.y << ", " << physicsRot.z << ")" << endl;
        
        // Convert to Unreal coordinates (simulated)
        cout << "Converted to Unreal coordinates (simulated):" << endl;
        cout << "UE Position: (" << physicsPos.x * 100 << ", " << physicsPos.y * 100 
             << ", " << physicsPos.z * 100 << ") cm" << endl;
        
        // Show material properties
        UnrealPhysicsBridge::MaterialProperties props;
        props.friction = 0.7f;
        props.restitution = 0.3f;
        props.density = 1000.0f;
        props.isStatic = false;
        
        cout << "Material Properties:" << endl;
        cout << "Friction: " << props.friction << endl;
        cout << "Restitution: " << props.restitution << endl;
        cout << "Density: " << props.density << " kg/m³" << endl;
        cout << "Is Static: " << (props.isStatic ? "Yes" : "No") << endl;
    }
};

int main() {
    cout << "=== 3D Physics Engine for Unreal Engine ===" << endl;
    cout << "This physics engine provides:" << endl;
    cout << "- Rigid body dynamics with mass, inertia, and forces" << endl;
    cout << "- Collision detection (sphere, box, plane)" << endl;
    cout << "- Contact resolution with friction and restitution" << endl;
    cout << "- Unreal Engine integration utilities" << endl;
    cout << "- Force generators (gravity, springs, buoyancy)" << endl;
    cout << "- Sleep/wake system for performance" << endl;
    cout << endl;
    
    try {
        // Create and run physics example
        PhysicsExample example;
        
        // Run simulation
        example.runSimulation(5.0f);
        
        // Demonstrate Unreal integration
        example.demonstrateUnrealIntegration();
        
        // Show final statistics
        cout << "\n--- Final Statistics ---" << endl;
        auto stats = example.world.getStats();
        cout << "Total Bodies: " << stats.bodyCount << endl;
        cout << "Total Contacts: " << stats.contactCount << endl;
        cout << "Total Kinetic Energy: " << stats.totalKineticEnergy << " J" << endl;
        cout << "Total Potential Energy: " << stats.totalPotentialEnergy << " J" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    cout << "\nPhysics engine demonstration complete!" << endl;
    cout << "To integrate with Unreal Engine:" << endl;
    cout << "1. Include the UnrealPhysicsBridge.h in your Unreal project" << endl;
    cout << "2. Replace UE:: namespace references with actual Unreal Engine types" << endl;
    cout << "3. Use UnrealPhysicsBridge functions to sync between physics and Unreal" << endl;
    cout << "4. Set up collision callbacks and event handling" << endl;
    
    return 0;
}
