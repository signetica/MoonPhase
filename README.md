# MoonPhase
C++ class for calculating the phase and position of the moon for Unix, Linux, Arduino

## Overview
Calculate the phase and position of the moon for a given date.

## Synopsis
Determine the phase of the moon and its the ecliptic coordinates (ecliptic
latitude, ecliptic longitude, and distance) for the specified time in seconds
since the Unix epoch (January 1, 1970).  The name of the moon phase (New, Full, etc.)
and the name of the Zodiac constellation the moon is in are also provided.

## Discussion and Applicability
The algorithm is simple and adequate for many purposes.  It requires very
little computational effort and is suitable for small embedded systems.  For
systems with small 4-byte double precision floating point types (such as early
Arduino processors) there is a special version of the software included in
this distribution (MoonPhaseFXP, for Floating X Precision) that avoids exceeding the
available precision.

To paraphrase the original author Bradley E Schaefer,

		I can only think of one application where lunar phase is needed to a
		hundredth of a day, whereas nearly all applications are happy to have
		one-day accuracy (which gives the phase to 3% accuracy).  If you need
		high accuracy, then you should be using some other program...  
		
		A limiting trouble is that the times of any particular lunar
		phase are not exactly periodic, but they wander around a bit,
		for example due to the usual effects of solar gravity.

## Historical background

This software was originally adapted to javascript by Stephen R. Schmitt
from a BASIC program from the 'Astronomical Computing' column of Sky & Telescope,
April 1994, page 84, written by Bradley E. Schaefer.

## Usage

### Detailed synopsis
MoonPhase mp(time_t time);

### Arguments
* time:		The time of the desired the moon phase and position, in GMT seconds from
		the Unix epoch (January 1, 1970).
		As the moon phase changes slowly and precision within a few
		hours is not likely necessary for most applications, using the
		time provided by the Arduino now(), which will be the time in
		seconds from January 1, 1970 in your local time zone, should
		be fine.

### Returned values
* double jDate:		The fractional Julian date for *time*.

* double phase:	      	The phase of the moon, from 0 (new) to 0.5 (full) to 1.0 (new).

* double age:		Age in days of the current cycle.

* double fraction:	The illumination fraction, from 0% - 100%.

* double distance:	Moon distance in earth radii.

* double latitude:	Moon ecliptic latitude in degrees.

* double longitude:	Moon ecliptic longitude in degrees.

* const char *phaseName: The name of the moon phase: New, Full, etc.

* const char *zodiacName: The name of the Zodiac constellation the moon is in.
