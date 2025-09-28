# 3D Physics Engine for Unreal Engine

A comprehensive 3D physics engine written in C++ designed for integration with Unreal Engine. This engine provides realistic rigid body dynamics, collision detection, and contact resolution.

## Features

### Core Physics
- **Rigid Body Dynamics**: Mass, inertia, forces, and torques
- **Integration**: Verlet integration for stable physics simulation
- **Sleep System**: Automatic sleep/wake for performance optimization
- **Damping**: Linear and angular damping for realistic motion

### Collision Detection
- **Primitive Shapes**: Spheres, boxes, and planes
- **Broad Phase**: Simple broad phase collision detection
- **Narrow Phase**: Precise collision detection between primitives
- **Contact Generation**: Automatic contact point calculation

### Collision Response
- **Contact Resolution**: Position and velocity correction
- **Friction**: Static and dynamic friction simulation
- **Restitution**: Bounce and energy conservation
- **Impulse Application**: Realistic collision response

### Force Generators
- **Gravity**: Configurable gravitational force
- **Springs**: Hooke's law spring forces
- **Buoyancy**: Fluid dynamics simulation
- **Custom Forces**: Extensible force system

### Unreal Engine Integration
- **Coordinate Conversion**: Automatic conversion between physics and Unreal coordinates
- **Component Sync**: Synchronization with Unreal components
- **Event System**: Collision and trigger event handling
- **Material Properties**: Integration with Unreal's material system
- **Debug Drawing**: Visual debugging tools

## Project Structure

```
cpp-projects/
├── Math/                    # Mathematical utilities
│   ├── Vector3.h           # 3D vector class
│   ├── Quaternion.h        # Quaternion for rotations
│   └── Matrix3.h           # 3x3 matrix class
├── Physics/                # Core physics system
│   ├── RigidBody.h/cpp     # Rigid body dynamics
│   ├── PhysicsWorld.h/cpp  # Physics world management
│   └── ContactResolver.h   # Contact resolution
├── Collision/              # Collision detection
│   ├── CollisionPrimitive.h
│   └── CollisionDetector.cpp
├── UnrealIntegration/      # Unreal Engine integration
│   ├── UnrealPhysicsBridge.h
│   └── UnrealPhysicsBridge.cpp
├── 3DPhysicsEngine.cpp     # Main demo application
├── CMakeLists.txt          # Build configuration
└── README.md               # This file
```

## Building

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher

### Build Instructions

1. **Clone or download the project**
   ```bash
   git clone <repository-url>
   cd cpp-projects
   ```

2. **Create build directory**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake**
   ```bash
   cmake ..
   ```

4. **Build the project**
   ```bash
   cmake --build . --config Release
   ```

5. **Run the demo**
   ```bash
   ./bin/PhysicsEngine3D
   ```

### Windows (Visual Studio)
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

## Usage

### Basic Physics World Setup

```cpp
#include "Physics/PhysicsWorld.h"

// Create physics world
PhysicsWorld world(100, 10); // max contacts, iterations

// Set gravity
world.setGravity(Vector3(0, -9.81f, 0));

// Create a rigid body
auto body = std::make_unique<RigidBody>();
body->setMass(1.0f);
body->setPosition(Vector3(0, 5, 0));

// Add to world
world.addBody(std::move(body));
```

### Collision Detection

```cpp
#include "Collision/CollisionPrimitive.h"

// Create collision primitives
auto sphere = std::make_unique<CollisionSphere>(0.5f);
auto box = std::make_unique<CollisionBox>(Vector3(1, 1, 1));

// Set up collision detection
sphere->body = bodyA;
box->body = bodyB;

world.addPrimitive(sphere.get());
world.addPrimitive(box.get());
```

### Force Generators

```cpp
// Add gravity
auto gravity = std::make_unique<PhysicsWorld::Gravity>(Vector3(0, -9.81f, 0));
world.addForceGenerator(body.get(), gravity.get());

// Add spring force
auto spring = std::make_unique<PhysicsWorld::Spring>(
    Vector3(0, 0, 0),  // connection point
    otherBody,         // other body
    Vector3(0, 0, 0),  // other connection point
    1000.0f,          // spring constant
    2.0f              // rest length
);
world.addForceGenerator(body.get(), spring.get());
```

### Unreal Engine Integration

```cpp
#include "UnrealIntegration/UnrealPhysicsBridge.h"

// Convert Unreal coordinates to physics
Vector3 physicsPos = UnrealPhysicsBridge::UEToPhysics(ueActor->GetActorLocation());

// Set up physics body
body->setPosition(physicsPos);

// Run physics simulation
world.runPhysics(deltaTime);

// Sync back to Unreal
UnrealPhysicsBridge::SyncPhysicsToActor(*body, ueActor);
```

## Integration with Unreal Engine

### Setup Steps

1. **Copy Integration Files**: Copy the `UnrealIntegration/` folder to your Unreal project
2. **Replace UE:: Types**: Replace `UE::` namespace references with actual Unreal Engine types
3. **Include Headers**: Add the physics engine headers to your Unreal project
4. **Link Libraries**: Link the compiled physics engine library

### Example Unreal Component

```cpp
// In your Unreal component header
#include "UnrealPhysicsBridge.h"

UCLASS()
class YOURGAME_API UPhysicsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPhysicsComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    std::unique_ptr<RigidBody> physicsBody;
    std::unique_ptr<CollisionPrimitive> collisionPrimitive;
    PhysicsWorld* physicsWorld;
};
```

### Coordinate System Notes

- **Physics Engine**: Uses meters as units
- **Unreal Engine**: Uses centimeters as units
- **Conversion**: Automatic conversion handled by `UnrealPhysicsBridge`
- **Scale Factor**: Configurable scale factor for different world scales

## Performance Considerations

### Optimization Tips

1. **Use Sleep System**: Enable sleep for inactive bodies
2. **Limit Contact Count**: Set reasonable maximum contact limits
3. **Tune Iterations**: Adjust position and velocity iteration counts
4. **Broad Phase**: Implement spatial partitioning for large scenes
5. **Memory Pools**: Use object pooling for frequent allocations

### Recommended Settings

```cpp
// For 60 FPS simulation
world.setDamping(0.99f);
world.setLinearDamping(0.99f);
world.setAngularDamping(0.99f);

// Contact resolution
ContactResolver resolver(10, 10); // position, velocity iterations
```

## Advanced Features

### Custom Force Generators

```cpp
class CustomForce : public PhysicsWorld::ForceGenerator
{
public:
    virtual void updateForce(RigidBody* body, float duration) override
    {
        // Your custom force calculation
        Vector3 force = calculateCustomForce(body);
        body->addForce(force);
    }
};
```

### Collision Callbacks

```cpp
// Register collision event callback
UnrealPhysicsBridge::RegisterEventCallback(
    UnrealPhysicsBridge::PhysicsEvent::COLLISION_START,
    [](const UnrealPhysicsBridge::PhysicsEvent& event) {
        // Handle collision
        UE_LOG(LogTemp, Warning, TEXT("Collision detected!"));
    }
);
```

### Constraints

```cpp
// Create distance constraint
auto constraint = std::make_unique<UnrealPhysicsBridge::DistanceConstraint>(
    bodyA, bodyB, anchorA, anchorB, restLength
);
world.addConstraint(std::move(constraint));
```

## Troubleshooting

### Common Issues

1. **Compilation Errors**: Ensure C++17 support is enabled
2. **Link Errors**: Check that all source files are included in build
3. **Performance Issues**: Reduce iteration counts or enable sleep system
4. **Integration Issues**: Verify coordinate system conversions

### Debug Features

```cpp
// Enable debug drawing
UnrealPhysicsBridge::DrawPhysicsDebug(world, ueWorld);

// Print performance stats
auto stats = UnrealPhysicsBridge::GetPerformanceStats(world);
UnrealPhysicsBridge::LogPerformanceStats(stats);
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## License

This project is provided as-is for educational and development purposes. Please ensure compliance with Unreal Engine's licensing terms when integrating.

## Future Enhancements

- [ ] Soft body dynamics
- [ ] Fluid simulation
- [ ] Advanced collision shapes (convex hulls, meshes)
- [ ] Multi-threading support
- [ ] GPU acceleration
- [ ] Advanced constraint types
- [ ] Particle systems
- [ ] Cloth simulation

## References

- "Game Physics Engine Development" by Ian Millington
- "Real-Time Physics Class Notes" by Erin Catto
- Unreal Engine Documentation
- Bullet Physics Library
