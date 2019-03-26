#ifndef PICORNT_H_
#define PICORNT_H_
/*
 *  This code is released under the MIT License.
 *  Copyright (c) 2013 Nenad Markus
 */

#pragma once

/*
	
*/


// * `angle` is a number between 0 and 1 that determines the counterclockwise in-plane rotation of the cascade:
//		0.0f corresponds to 0 radians and 1.0f corresponds to 2*pi radians

unsigned int find_objects
		(
			float rcsq[], unsigned int maxndetections,
			void* cascade, float angle,
			void* pixels, unsigned int nrows, unsigned int ncols, unsigned int ldim,
			float scalefactor, float stridefactor, float minsize, float maxsize
		);

unsigned int cluster_detections(float rcsq[], unsigned int n);

#endif // PICORNT_H_
