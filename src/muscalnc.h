/**
 * @file muscalnc.h
 * @brief Main header file for MUSCALNC library.
 * @version 1.0
 *
 * Delivers the MUSCALNC model 
 *
 */
#ifndef MUSCALNC_H
#define MUSCALNC_H

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "muscalnc_dataset.h"

/** Defines a return value of success */
#define SUCCESS 0
/** Defines a return value of failure */
#define FAIL 1

/* config string */
#define MUSCALNC_CONFIG_MAX 1000
#define MUSCALNC_DATASET_MAX 1

extern int muscalnc_ucvm_debug;
extern int muscalnc_ucvm_debug_detail;
extern FILE *stderrfp;

// Structures
/** Defines a point (latitude, longitude, and depth) in WGS84 format */
typedef struct muscalnc_point_t {
	/** Longitude member of the point */
	double longitude;
	/** Latitude member of the point */
	double latitude;
	/** Depth member of the point */
	double depth;
} muscalnc_point_t;

/** Defines the material properties this model will retrieve. */
typedef struct muscalnc_properties_t {
	/** P-wave velocity in meters per second */
	double vp;
	/** S-wave velocity in meters per second */
	double vs;
	/** Density in g/m^3 */
	double rho;
	/** Qp */
	double qp;
	/** Qs */
	double qs;
} muscalnc_properties_t;

/**
Dimensions: 3
  dim[0] name=depth len=84
  dim[1] name=latitude len=381
  dim[2] name=longitude len=471
Total elements: 15073884
**/

/** The MUSCALNC configuration structure. */
typedef struct muscalnc_configuration_t {
	/** The zone of UTM projection */
	int utm_zone;
	/** The model directory */
	char model_dir[128];

	/** interpolation on or off (1 or 0) */
	int interpolation;
	/** use_binary on or off (1 or 0) */
	int use_binary;
	/** too_big on or off (1 or 0) */
	int too_big;
	/** add muscalnc1d on or off (1 or 0) */
	int enable_1d;

        /* how many datasets are in the model */
        int dataset_cnt;
        char *dataset_files[MUSCALNC_DATASET_MAX];  //strdup
	char *dataset_labels[MUSCALNC_DATASET_MAX]; // strdup
        char *surface_files[MUSCALNC_DATASET_MAX];  //strdup
        int surface_counts[MUSCALNC_DATASET_MAX];
						  
} muscalnc_configuration_t;

typedef struct muscalnc_model_t {
        int dataset_cnt;
        muscalnc_dataset_t *datasets[MUSCALNC_DATASET_MAX];
} muscalnc_model_t;


// Constants
/** The version of the model. */
extern const char *muscalnc_version_string;

// Variables
/** Set to 1 when the model is ready for query. */
extern int muscalnc_is_initialized;

/** Configuration parameters. */
extern muscalnc_configuration_t *muscalnc_configuration;

/** Holds pointers to the velocity model data OR indicates it can be read from file. */
extern muscalnc_model_t *muscalnc_velocity_model;

// UCVM API Required Functions

#ifdef DYNAMIC_LIBRARY

/** Initializes the model */
int model_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int model_finalize();
/** Returns version information */
int model_version(char *ver, int len);
/** Queries the model */
int model_query(muscalnc_point_t *points, muscalnc_properties_t *data, int numpts);

int (*get_model_init())(const char *, const char *);
int (*get_model_query())(muscalnc_point_t *, muscalnc_properties_t *, int);
int (*get_model_finalize())();
int (*get_model_version())(char *, int);

#endif

// MUSCALNC Related Functions

/** Initializes the model */
int muscalnc_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int muscalnc_finalize();
/** Returns version information */
int muscalnc_version(char *ver, int len);
/** Queries the model */
int muscalnc_query(muscalnc_point_t *points, muscalnc_properties_t *data, int numpts);

// Non-UCVM Helper Functions
//
/** Reads the configuration file and helper functions. */
int muscalnc_read_configuration(char *file, muscalnc_configuration_t *config);
int muscalnc_configuration_finalize(muscalnc_configuration_t *config);

/** Prints out the error string. */
void muscalnc_print_error(char *err);
/** Retrieves the value at a specified grid point in the model. */
void muscalnc_read_properties(int x, int y, int z, muscalnc_properties_t *data);
/** Attempts to malloc the model size in memory and read it in. */
int muscalnc_read_model(muscalnc_configuration_t *config, muscalnc_model_t *model, char* dir);
/** toggle debug flag **/
void muscalnc_setdebug();

/** helper function for velocity_model **/
int muscalnc_velocity_model_init(muscalnc_model_t *model);
int muscalnc_velocity_model_finalize(muscalnc_model_t *model);

/** parse JSON metadata blob per dataset **/
int _setup_a_dataset(muscalnc_configuration_t *conf, char *blobstr);

void _trimLast(char *str, char m);
void _splitline(char* lptr, char key[], char value[]);

#endif
