/**
 * @file muscalnc_dataset.h
 *
**/

#ifndef MUSCALNC_DATASET_H
#define MUSCALNC_DATASET_H

// setup for future possible expansion
#define MUSCALNC_DATASET_MAX 1

#define MUSCALNC_CACHE_LAYER_MAX 20
#define MUSCALNC_CACHE_COL_MAX 10

#include "kdtree_util.h"

typedef struct muscalnc_properties_t muscalnc_properties_t;

typedef struct muscalnc_cache_layer_t {
     int cache_layer_dep_idx;
     float *layer_vp_buffer; // nx * ny
     float *layer_vs_buffer;
     float *layer_rho_buffer;
} muscalnc_cache_layer_t;


typedef struct muscalnc_cache_col_t {
     int cache_col_lat_idx;
     int cache_col_lon_idx;
     float *col_vp_buffer; // nz
     float *col_vs_buffer;
     float *col_rho_buffer;
} muscalnc_cache_col_t;


/** The MUSCALNC a dataset's working structure. */
typedef struct muscalnc_dataset_t {
	/** tracking netcdf id **/
        int ncid;

	/** Number of x(lon) points */
	int nx;
	/** Number of y(lat) points */
	int ny;
	/** Number of z(dep) points */
	int nz;

        /* surfaces  */
        KDNodeSetup *kdsurface;

	/** list of longitudes **/
	float *longitudes;
	/** list of latitudes **/
	float *latitudes;
	/** list of depths **/
	float *depths;

	int vp_varid;
	int vs_varid;
	int rho_varid;

	int elems;
	float *vp_buffer;
	float *vs_buffer;
	float *rho_buffer; 

	// track how many cached layers
        int layer_cache_cnt;
        muscalnc_cache_layer_t *layer_cache[MUSCALNC_CACHE_LAYER_MAX];

/* a cache of previous column from cache_depth_col_float call */
	int col_cache_cnt;
        muscalnc_cache_col_t *col_cache[MUSCALNC_CACHE_COL_MAX];

/* flag to show if data i read in memory */
        int in_memory;

} muscalnc_dataset_t;

typedef struct muscalnc_pt_info_t {
	float lon;
	float lat;
	float dep;
        int lon_idx;
	int lat_idx;
	int dep_idx;
	float lon_percent;
	float lat_percent;
	float dep_percent;
} muscalnc_pt_info_t;

/* utilitie functions */
muscalnc_dataset_t *make_a_muscalnc_dataset(char *datadir, char *datafile, int tooBig, int useBinary);
int free_muscalnc_dataset(muscalnc_dataset_t *data);
muscalnc_cache_col_t *find_a_cache_col(muscalnc_dataset_t *dataset, int target_lat_idx, int target_lon_idx);
void free_a_cache_col(muscalnc_cache_col_t *col);
muscalnc_cache_layer_t *find_a_cache_layer(muscalnc_dataset_t *dataset, int target_dep_idx);
void free_a_cache_layer(muscalnc_cache_layer_t *layer);
void add_surface_data(muscalnc_dataset_t  *data, char *sfile, int s_count);

int get_one_property(muscalnc_dataset_t *dataset, muscalnc_pt_info_t *pt, muscalnc_properties_t *data);
int get_one_muscalnc1d_property(muscalnc_dataset_t *dataset, muscalnc_pt_info_t *pt, muscalnc_properties_t *data);
void get_interp_property(muscalnc_dataset_t *dataset, muscalnc_pt_info_t *pt, muscalnc_properties_t *data);


#endif

