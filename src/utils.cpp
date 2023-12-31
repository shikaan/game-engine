#include "utils.h"

#include <cmath>
#include <cstdio>
#include <ctime>
#include <thread>

char *getTimeString() {
  static char time_str[30];

  time_t now;
  time(&now);
  struct tm *p_localtime = localtime(&now);

  sprintf(time_str, "%02d:%02d:%02d", p_localtime->tm_hour, p_localtime->tm_min,
          p_localtime->tm_sec);

  return time_str;
}

void sleep(long int microseconds) {
  std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}

bool match(df::Vector p1, df::Vector p2) {
  return std::abs(p1.getX() - p2.getX()) <= 1 &&
         std::abs(p1.getY() - p2.getY()) <= 1;
}

bool equals(float a, float b, float tolerance) {
  return std::abs(b - a) < tolerance;
}

bool intersects(df::Box a, df::Box b) {
  float aLeft = a.getCorner().getX();
  float aRight = aLeft + a.getWidth();
  float aTop = a.getCorner().getY();
  float aBottom = aTop + a.getHeight();

  float bLeft = b.getCorner().getX();
  float bRight = bLeft + b.getWidth();
  float bTop = b.getCorner().getY();
  float bBottom = bTop + b.getHeight();

  bool xOverlap = (bLeft <= aLeft && aLeft <= bRight) ||
                  (aLeft <= bLeft && bLeft <= aRight);
  bool yOverlap =
      (bTop <= aTop && aTop <= bBottom) || (aTop <= bTop && bTop <= aBottom);

  return xOverlap && yOverlap;
}
