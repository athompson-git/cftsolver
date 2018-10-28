#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>

#include <chrono>
#include <thread>


class Pendulum {

  public:
    // constructor
    Pendulum();
    Pendulum(double, double, double);
    //~Pendulum();

    // Params and initial conditions.
    double g; // m/s/s
    double l;
    double theta_0; // initial angle in rad
    double step;

    double theta;  // rad
    double last_theta;
    double t;

    double GetTime() {return t;}
    double GetAngle() {return theta;}
    void TimeStep(void);
    void UpdateSmallAngle(void);

    double GetX();
    double GetY();

    void Update(void);


};


// Default constructor
Pendulum::Pendulum() {
  g = 9.8;
  l = 5.0;
  theta_0 = 0.9;
  theta = theta_0;
  last_theta = theta_0;
  step = 0.01;
}


// Constructor with args.
Pendulum::Pendulum(double length, double angle, double step_size) {
  g = 9.8; // m/s
  l = length;
  last_theta = angle;
  theta_0 = angle;
  theta = theta_0;
  step = step_size;
}


// Step forward.
void Pendulum::TimeStep() {
  std::this_thread::sleep_for(std::chrono::nanoseconds(1));
  t += step;
}


// Step forward (theta).
void Pendulum::UpdateSmallAngle() {
  last_theta = theta;
  theta = theta_0 * cos(sqrt(g/l) * t);
}


// Get cartesian state.
double Pendulum::GetX() {
  return l * sin(theta);
}

double Pendulum::GetY() {
  return l * cos(theta);
}


void Pendulum::Update() {
  last_theta = theta;
  theta = (2*theta) - last_theta - pow(step, 2)*(g/l)*sin(theta);
  //std::cout << theta << std::endl;
}


int main() {

  double set_l, set_angle, set_step;
/*
  printf("input length: \n");
  scanf("%lf", &set_l);
  printf("input initial angle: \n");
  scanf("%lf", &set_angle);
  printf("input step size: \n");
  scanf("%lf", &set_step);
*/

  Pendulum bob;

  while (bob.GetAngle() > 0.0001) {
    bob.TimeStep();
    printf("%f\n", bob.GetAngle());
    bob.Update();
  }
  return 0;

}

