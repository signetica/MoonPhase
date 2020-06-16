// Calculate the phase and position of the moon for a given date.
// The algorithm is simple and adequate for many purposes.
//
// This software was originally adapted to javascript by Stephen R. Schmitt
// from a BASIC program from the 'Astronomical Computing' column of Sky & Telescope,
// April 1994, page 84, written by Bradley E. Schaefer.
//
// Subsequently adapted from Stephen R. Schmitt's javascript to c++ for the Arduino
// by Cyrus Rahman, this work is subject to Stephen Schmitt's copyright:
//
// Copyright 2004 Stephen R. Schmitt
// You may use or modify this source code in any way you find useful, provided
// that you agree that the author(s) have no warranty, obligations or liability.  You
// must determine the suitability of this source code for your use.

#include <math.h>
#include "MoonPhaseFXP.h"

// Names of lunar phases
static const char *phaseNames[] = {"New", "Evening Crescent", "First Quarter",
				   "Waxing Gibbous", "Full", "Waning Gibbous",
				   "Last Quarter", "Morning Crescent"};
// Names of Zodiac constellations
static const char *zodiacNames[] = {"Pisces", "Aries", "Taurus", "Gemini", "Cancer",
				    "Leo", "Virgo", "Libra", "Scorpio", "Sagittarius",
				    "Capricorn", "Aquarius"};
// Ecliptic angles of Zodiac constellations
static const float zodiacAngles[] = {33.18, 51.16, 93.44, 119.48, 135.30, 173.34,
				     224.17, 242.57, 271.26, 302.49, 311.72, 348.58};

// Determine Julian day from Unix time.
long julianDay(time_t t) {
  return ((long)((t / 86400.0L) + 0.5) + 2440587);
}

#ifdef notdef
// Determine Julian date from Unix time.
// Provides marginally accurate results with older Arduino 4-byte double.
double julianDate(time_t t) {
  return (t / 86400.0L + 2440587.5);
}
#endif

// Return the fractional Julian Date, e.g. fraction of day after 1200UTC.
double julianDateFrac(time_t t) {
  double f = t / 86400.0L + 0.5;
  f -= floor(f);
  return (f);
}

// Determine the Moon Phase and orbital positions for the specified time.
void
MoonPhaseFXP::calculate(time_t t) {
  long jDay = julianDay(t);
  jDate = jDay;
  double jDateFrac = julianDateFrac(t);

  // Calculate illumination (synodic) phase.
  // From number of days since new moon on Julian date MOON_SYNODIC_OFFSET
  // (1815UTC January 6, 2000), determine remainder of incomplete cycle.
  //
  // The calculation is convoluted because if we only have four-byte
  // floats on an older Arduino, we must avoid exceeding the available precision.
  // We can do this by subtracting the large integers first, then
  // dealing with the smaller partial days.
  //
  // With an 8-byte double this could simplified:
  //  Use (double) julianDate() to return the fractional Julian date
  //  and calculate the phase directly:
  //   jDate = julianDate(t);
  //   phase = (jDate - MOON_SYNODIC_OFFSET) / MOON_SYNODIC_PERIOD;
  //
  phase = ((jDay - 2451550L) - 0.26 + jDateFrac) / MOON_SYNODIC_PERIOD;
  phase -= floor(phase);

  // Calculate age and illumination fraction.
  age = phase * MOON_SYNODIC_PERIOD;
  fraction = (1.0 - cos(2 * M_PI * phase)) * 0.5;
  phaseName = phaseNames[(int)(phase * 8 + 0.5) % 8];

  // Calculate distance from anomalistic phase (offset 2451562.2).
  double distancePhase = ((jDay - 2451562L) - 0.2 + jDateFrac) / MOON_DISTANCE_PERIOD;
  distancePhase -= floor(distancePhase);
  distance = 60.4 - 3.3 * cos(2 * M_PI * distancePhase)
		  - 0.6 * cos(2 * 2 * M_PI * phase - 2 * M_PI * distancePhase)
		  - 0.5 * cos(2 * 2 * M_PI * phase);

  // Calculate ecliptic latitude from nodal (draconic) phase (offset 2451565.2).
  double latPhase = ((jDay - 2451565L) - 0.2 + jDateFrac) / MOON_LATITUDE_PERIOD;
  latPhase -= floor(latPhase);
  latitude = 5.1 * sin(2 * M_PI * latPhase);

  // Calculate ecliptic longitude from sidereal motion (offset 2451555.8).
  double longPhase = ((jDay - 2451555L) - 0.8 + jDateFrac) / MOON_LONGITUDE_PERIOD;
  longPhase -= floor(longPhase);
  longitude = 360 * longPhase
	      + 6.3 * sin(2 * M_PI * distancePhase)
	      + 1.3 * sin(2 * 2 * M_PI * phase - 2 * M_PI * distancePhase)
	      + 0.7 * sin(2 * 2 * M_PI * phase);
  if (longitude > 360)
    longitude -= 360;

  // Select the Zodiac name.
  zodiacName = zodiacNames[0];
  for (int i = 0; i < sizeof(zodiacAngles) / sizeof(float); i++) {
    if (longitude < zodiacAngles[i]) {
      zodiacName = zodiacNames[i];
      break;
    }
  }
}
