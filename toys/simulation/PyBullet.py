import pybullet as p
import pybullet_data
import time

def main():
    # Connect to the physics server in DIRECT mode.
    physicsClient = p.connect(p.DIRECT)

    # Set the search path for URDF files provided by PyBullet.
    p.setAdditionalSearchPath(pybullet_data.getDataPath())

    # Reset simulation to ensure a clean start.
    p.resetSimulation()

    # Set gravity (x, y, z); here we simulate Earth's gravity.
    p.setGravity(0, 0, -9.81)

    # Load a ground plane using a URDF file.
    planeId = p.loadURDF("plane.urdf")

    # Define the initial position and orientation for a robot/object.
    startPos = [0, 0, 1]  # Position in world coordinates
    startOrientation = p.getQuaternionFromEuler([0, 0, 0])  # No initial rotation

    # Load an example robot (R2D2) using its URDF file.
    objectId = p.loadURDF("r2d2.urdf", startPos, startOrientation)

    # Run the simulation loop.
    for i in range(10000):
        # Advance the simulation by one time step.
        p.stepSimulation()
        # Sleep to simulate real-time (using a 240Hz time step).
        time.sleep(1. / 240.)

    # Disconnect from the physics server.
    p.disconnect()

if __name__ == "__main__":
    main()