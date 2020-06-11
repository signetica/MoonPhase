#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "MoonPhaseFXP.h"

// Print the moon phase data on stdout.  Takes an optional argument of the Unix
// time in seconds from Jan 1, 1970 for the desired date.
int main(int argc, char *argv[]) {

  // Default to the current time.
  time_t t = time(NULL);

  // Look for an argument.
  if (argc > 1)
    t = atol(argv[1]);

  // Calculate the moon phase and related information.
  MoonPhase m(t);

  printf("Time:\t\t\t%s", ctime(&t));
  printf("Julian Day:\t\t%ld\nPhase:\t\t\t%.2f\nAge:\t\t\t%.2f\n"
	 "Illumination Fraction:\t%.2f\n"
	 "Distance:\t\t%.2f earth radii\nEcliptic Latitude:\t%.2f\n"
	 "Ecliptic Longitude:\t%.2f\n",
	 m.jDay, m.phase, m.age, m.fraction, m.distance, m.latitude, m.longitude);
  printf("Lunar Phase:\t\t%s\n", m.phaseName);
  printf("Lunar Zodiac Transit:\t%s\n", m.zodiacName);

  exit(0);
}
