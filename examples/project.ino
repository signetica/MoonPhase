#include <TimeLib.h>
#include <MoonPhase.h>

void
setup() {

  double latitude = 42;
  double longitude = -90;

  time_t t = now();

  // Calculate the moon phase and related information.
  MoonPhase m(t);

}

// Now do something with the result in your loop().
void
loop() {

// Here are the returned values you can use:
//	Julian Day:			m.jDate
//	Phase:				m.phase
//	Age:				m.age
//	Illumination Fraction:		m.fraction
//	Distance (in earth radii):	m.distance
//	Ecliptic Latitude:		m.latitude
//	Ecliptic Longitude:		m.longitude

}
