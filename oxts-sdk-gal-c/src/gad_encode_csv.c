
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "oxts/gal-c/gad_encode_csv.h"
#include "oxts/core/errors.h"
#include "oxts/core/BasicCasts.h"


#ifdef __cplusplus
extern "C"
{
#endif
   

#define MAX_BUFF 1024

   //============================================================================================================
   int print_gen_3d_header(FILE* file_ptr)
   {
#ifdef EXTRA_CHECKS
      if (file_ptr == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to file");
         return -1;
      }
#endif

      int i = 0;
      if (fprintf(file_ptr, "mode,x_type,x[0],x[1],x[2],v_type,v[0],v[1],v[2],v[3],v[4],v[5],") < 0)
         i = -1;

      return i;
   }



   int init_gad_output_file(FILE* gad_engine_file_ptr)
   {
#ifdef EXTRA_CHECKS
      if (gad_engine_file_ptr == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to file");
         return -1;
      }
#endif
      int i = 0;

      // write generic aiding struct header to csv file
      if (i);
      else if ((fprintf(gad_engine_file_ptr, "#ver,type,stream ID,") < 0))
         i = -1;
      else if (fprintf(gad_engine_file_ptr, "val_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "time_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "acq_valid,") < 0)
         i = -1;
      else if (fprintf(gad_engine_file_ptr, "acq_time,") < 0)
         i = -1;
      else if (fprintf(gad_engine_file_ptr, "loc_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "res1_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "res2_valid,") < 0)
         i = -1;
      else if ((i = print_gen_3d_header(gad_engine_file_ptr)));
      else if (fprintf(gad_engine_file_ptr, "\n") < 0);
      else if (fflush(gad_engine_file_ptr) != 0)
         i = -1;

      return i;
   }
   //============================================================================================================
   //! \brief writes the contents of the GEN_3D to csv

   int encode_gen_3d_to_csv(char * out_string, int * offset_ptr, GEN_3D* g)
   {
      int i = 0;

      if ((*offset_ptr += sprintf(out_string + *offset_ptr, 
         "%d,%d,%.12f,%.12f,%.12f,%d,%.12f,%.12f,%.12f,%.12f,%.12f,%.12f,",
         g->mode,
         g->x_type,
         g->x[0], g->x[1], g->x[2],
         g->v_type,
         g->v[0], g->v[1], g->v[2], g->v[3], g->v[4], g->v[5]))
         < 0)
      {
         i = -1;
      }
      return i;
   }


   int write_gen_3d(FILE* file_ptr, GEN_3D* gen_3d_data)
   {
      int i = 0;
      unsigned char out_string[MAX_BUFF];
      int offset = 0;
      int * offset_ptr = &offset;
      encode_gen_3d_to_csv(out_string,offset_ptr,gen_3d_data);
      fputs(out_string,file_ptr);

      return 0;
   }


   /*

   */
   int encode_gad_to_csv(char * out_string, int * offset_ptr, GEN_AIDING_DATA* data)
   {
#ifdef EXTRA_CHECKS
      if (out_string == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to array");
         return -1;
      }
      if (data == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to generic aiding structure");
         return -1;
      }
#endif

      int i = 0; // 0 means no errors encountered

      if (i);
      // write ver
      else if ((*offset_ptr +=sprintf(out_string + *offset_ptr, "%d,", 0)) < 0)
         i = -1;
      // write type
      else if ((*offset_ptr +=sprintf(out_string + *offset_ptr, "%d,", data->type)) < 0)
         i = -1;
      // write stream ID
      if ((*offset_ptr +=sprintf(out_string + *offset_ptr, "%d,", data->stream_id)) < 0)
         i = -1;

      // write val
      if ((*offset_ptr +=sprintf(out_string + *offset_ptr, "%d,", data->val_valid)) < 0)
         i = -1;

      if (!i && data->val_valid)
         i = encode_gen_3d_to_csv(out_string,offset_ptr, &data->val);
      else if (!i && !data->val_valid)
         (i = (*offset_ptr +=sprintf(out_string + *offset_ptr, ",,,,,,,,,,,,")) < 0) ? -1 : 0;

      // write time
      if ((*offset_ptr +=sprintf(out_string + *offset_ptr, "%d,", data->time_valid)) < 0)
         i = -1;

      if (!i)// && data->time_valid)
         i = encode_gen_3d_to_csv(out_string,offset_ptr, &data->time);
      else if (!i && !data->time_valid)
         (i = (*offset_ptr +=sprintf(out_string + *offset_ptr, ",,,,,,,,,,,,")) < 0) ? -1 : 0;

      // write acq_time
      if ((*offset_ptr +=sprintf(out_string + *offset_ptr, "%d,", data->acq_valid)) < 0)
         i = -1;

      if (!i && data->acq_valid)
         (i = (*offset_ptr +=sprintf(out_string + *offset_ptr, "%u,", data->acq)) < 0);
      else if (!i && !data->acq_valid)
         (i = (*offset_ptr +=sprintf(out_string + *offset_ptr, ",")) < 0) ? -1 : 0;

      // write loc
      if ((*offset_ptr +=sprintf(out_string + *offset_ptr, "%d,", data->loc_valid)) < 0)
         i = -1;

      if (!i && data->loc_valid)
         i = encode_gen_3d_to_csv(out_string,offset_ptr, &data->loc);
      else if (!i && !data->loc_valid)
         (i = (*offset_ptr +=sprintf(out_string + *offset_ptr, ",,,,,,,,,,,,")) < 0) ? -1 : 0;

      // write res1
      if ((*offset_ptr +=sprintf(out_string + *offset_ptr, "%d,", data->res1_valid)) < 0)
         i = -1;

      if (!i && data->res1_valid)
         i = encode_gen_3d_to_csv(out_string,offset_ptr, &data->res1);
      else if (!i && !data->res1_valid)
         (i = (*offset_ptr +=sprintf(out_string + *offset_ptr, ",,,,,,,,,,,,")) < 0) ? -1 : 0;

      // write res2
      if ((*offset_ptr +=sprintf(out_string + *offset_ptr, "%d,", data->res2_valid)) < 0)
         i = -1;

      if (!i && data->res2_valid)
         i = encode_gen_3d_to_csv(out_string,offset_ptr, &data->res2);
      else if (!i && !data->res2_valid)
         (i = (*offset_ptr +=sprintf(out_string + *offset_ptr, ",,,,,,,,,,,,")) < 0) ? -1 : 0;

      *offset_ptr +=sprintf(out_string + *offset_ptr, "\n");
   }


   int write_gad_to_csv(FILE* file_ptr, GEN_AIDING_DATA* data)
   {
#ifdef EXTRA_CHECKS
      if (file_ptr == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to file");
         return -1;
      }
      if (data == NULL)
      {
         oxts_error(1, "NULL encountered instead of pointer to generic aiding structure");
         return -1;
      }
#endif

      int i = 0;
      unsigned char out_string[MAX_BUFF];
      int offset = 0;
      int * offset_ptr = &offset;

      if (i = encode_gad_to_csv(out_string,offset_ptr, data));
      fputs(out_string, file_ptr);
      fflush(file_ptr);
      return i;
   }



#ifdef __cplusplus
}
#endif