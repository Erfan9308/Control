import numpy as np
import matplotlib.pyplot as plt


# Define PID controller
class PIDController:
    def __init__(self, Kp, Ki, Kd, setpoint=0):
        self.Kp = Kp  # Proportional gain
        self.Ki = Ki  # Integral gain
        self.Kd = Kd  # Derivative gain
        self.setpoint = setpoint  # Desired value (reference)
        self.integral = 0  # Initialize integral term
        self.previous_error = 0  # Initialize previous error

    def compute(self, current_value, dt):
        error = self.setpoint - current_value
        self.integral += error * dt  # Integral term
        derivative = (error - self.previous_error) / dt  # Derivative term

        # PID formula
        output = self.Kp * error + self.Ki * self.integral + self.Kd * derivative

        self.previous_error = error  # Store error for next loop
        return output


# Define the system dynamics
def system_dynamics(current_position, input_force, K=1.0, tau=1.0):
    # Simple first-order system: K/(tau * s + 1)
    # Difference equation approximation for continuous system
    d_position = (K * input_force - current_position) / tau
    return d_position


# Simulation parameters
dt = 0.01  # Time step
simulation_time = 10  # Total simulation time
time = np.arange(0, simulation_time, dt)  # Time array

# Initialize system
current_position = 0  # Initial position
positions = []  # List to store positions over time
setpoint = 1.0  # Desired position

# Create PID controller
pid = PIDController(Kp=1.5, Ki=5.0, Kd=0.1, setpoint=setpoint) # By adding kp, the overshoots increase

                          # By lowering the Kd, the initial oscilation has been eliminated
                          # by adding to Ki, the whole diagram is become denser, thus increasing the overshoot,
                          # and lower settling time

# Run the simulation
for t in time:
    # Compute the PID control input
    input_force = pid.compute(current_position, dt)

    # Update the system dynamics (position)
    current_position += system_dynamics(current_position, input_force) * dt

    # Store the current position
    positions.append(current_position)

# Plot the results
plt.plot(time, positions, label="Position")
plt.axhline(y=setpoint, color='r', linestyle='--', label="Setpoint")
plt.xlabel('Time [s]')
plt.ylabel('Position')
plt.title('PID Controller Simulation')
plt.legend()
plt.grid(True)
plt.show()
