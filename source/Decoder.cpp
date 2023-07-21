#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef unsigned char U8;   /**< @brief 8-bits unsigned integer               */
typedef unsigned int U32;  /**< @brief 32-bits unsigned integer              */
typedef unsigned __int64 U64;     /**< @brief 64-bits unsigned integer              */
typedef signed char I8;
typedef short I16;          /**< @brief 16-bits signed integer                */
typedef int I32;           /**< @brief 32-bits signed integer                */
typedef __int64 I64;      /**< @brief 64-bits signed integer                */
typedef float F32;          /**< @brief 32-bits float pointer value           */
typedef unsigned short U16; /**< @brief 16-bits unsigned integer              */
typedef double F64;    
void main()
{
	FILE* fp=fopen("male02.bin","rb");
	if(fp)
	{
		char buff[258000];
		char* parser;
		size_t buffsize=fread(buff,1,258000,fp);
		char signature[13];
		parser=buff;
		memcpy(signature,parser,12);
		signature[12]='\0';
		printf("%s",signature);
		
		parser+=12;
		U8 header_bytes;
		memcpy(&header_bytes,parser,1);
		parser+=1;


		

		U8 vertex_coordinate_bytes;
		memcpy(&vertex_coordinate_bytes,parser,1);
		parser+=1;
		U8 normal_coordinate_bytes;
		memcpy(&normal_coordinate_bytes,parser,1);
		parser+=1;
		U8 uv_coordinate_bytes;
		memcpy(&uv_coordinate_bytes,parser,1);
		parser+=1;

		U8 vertex_index_bytes;
		memcpy(&vertex_index_bytes,parser,1);
		parser+=1;
		U8 normal_index_bytes;
		memcpy(&normal_index_bytes,parser,1);
		parser+=1;
		U8 uv_index_bytes;
		memcpy(&uv_index_bytes,parser,1);
		parser+=1;
		U8 material_index_bytes;
		memcpy(&material_index_bytes,parser,1);
		parser+=1;

		U32 nvertices;
		memcpy(&nvertices,parser,4);
		parser+=4;
		U32 nnormals;
		memcpy(&nnormals,parser,4);
		parser+=4;
		U32 nuvs;
		memcpy(&nuvs,parser,4);
		parser+=4;          

		U32 ntri_flat;
		memcpy(&ntri_flat,parser,4);
		parser+=4;     
		U32 ntri_smooth;
		memcpy(&ntri_smooth,parser,4);
		parser+=4;   
		U32 ntri_flat_uv;
		memcpy(&ntri_flat_uv,parser,4);
		parser+=4;  
		U32 ntri_smooth_uv;
		memcpy(&ntri_smooth_uv,parser,4);
		parser+=4;

		U32 nquad_flat;
		memcpy(&nquad_flat,parser,4);
		parser+=4;    
		U32 nquad_smooth;
		memcpy(&nquad_smooth,parser,4);
		parser+=4;  
		U32 nquad_flat_uv;
		memcpy(&nquad_flat_uv,parser,4);
		parser+=4; 
		U32 nquad_smooth_uv;
		memcpy(&nquad_smooth_uv,parser,4);
		parser+=4;


		int numofbytes=nvertices*3*vertex_coordinate_bytes;
		F32* Vertices=(F32*)malloc(numofbytes);
		memcpy(Vertices,parser,numofbytes);
		parser+=numofbytes;

		F32 X=*(Vertices+(nvertices-1)*3);
		F32 Y=*(Vertices+(nvertices-1)*3+1);
		F32 Z=*(Vertices+(nvertices-1)*3+2);


		 numofbytes=nnormals*3*normal_coordinate_bytes;
		I8* Normals=(I8*)malloc(numofbytes);
		memcpy(Normals,parser,numofbytes);
		parser+=numofbytes;

		
		parser=parser+4-(nnormals*3*normal_coordinate_bytes)%4;




		 numofbytes=nuvs*2*uv_coordinate_bytes;
		F32* UVs=(F32*)malloc(numofbytes);
		memcpy(UVs,parser,numofbytes);
		parser+=numofbytes;

		
		numofbytes=ntri_smooth_uv*3*vertex_index_bytes;
		U32* Vertindices=(U32*)malloc(numofbytes);
		memcpy(Vertindices,parser,numofbytes);
		for(int i=0;i<ntri_smooth_uv;i++)
		{
			U32 x=*(Vertindices+i*3);
			U32 y=*(Vertindices+i*3+1);
			U32 z=*(Vertindices+i*3+2);
			printf("whatever");
		}
		parser+=numofbytes;
		 


		numofbytes=ntri_smooth_uv*3*normal_index_bytes;
		U32* Normindices=(U32*)malloc(numofbytes);
		memcpy(Normindices,parser,numofbytes);
		for(int i=0;i<ntri_smooth_uv;i++)
		{
			U32 x=*(Normindices+i*3);
			U32 y=*(Normindices+i*3+1);
			U32 z=*(Normindices+i*3+2);
			printf("whatever");
		}
		parser+=numofbytes;




		numofbytes=ntri_smooth_uv*3*uv_index_bytes;
		U32*UVindices=(U32*)malloc(numofbytes);
		memcpy(UVindices,parser,numofbytes);
		for(int i=0;i<ntri_smooth_uv;i++)
		{
			U32 x=*(UVindices+i*3);
			U32 y=*(UVindices+i*3+1);
			U32 z=*(UVindices+i*3+2);
			printf("whatever");
		}
		parser+=numofbytes;


		numofbytes=ntri_smooth_uv*1*sizeof(U16);
		U16* Materialindices=(U16*)malloc(numofbytes);
		memcpy(Materialindices,parser,numofbytes);
		
		parser+=numofbytes;


		fclose(fp);
		FILE* fpwrite=fopen("male02.obj","w");
		if(fpwrite)
		{
			fprintf(fpwrite,"mtllib male02.mtl\n");
			for(int i=0;i<nvertices;i++)
			{
				fprintf(fpwrite,"v %f %f %f\n",*(Vertices+i*3),*(Vertices+i*3+1),*(Vertices+i*3+2));
			}
			for(int i=0;i<nnormals;i++)
			{
				fprintf(fpwrite,"vn %f %f %f\n",*(Normals+i*3)/127.0,*(Normals+i*3+1)/127.0,*(Normals+i*3+2)/127.0);
			}
			for(int i=0;i<nuvs;i++)
			{
				fprintf(fpwrite,"vt %f %f\n",*(UVs+i*2),*(UVs+i*2+1));
			}

			for(int i=0;i<ntri_smooth_uv;i++)
			{
				fprintf(fpwrite,"usemtl mat%d\n",Materialindices[i]+1);
				fprintf(fpwrite,"f %d/%d/%d %d/%d/%d %d/%d/%d\n",*(Vertindices+i*3)+1,*(UVindices+i*3)+1,*(Normindices+i*3)+1,*(Vertindices+i*3+1)+1,*(UVindices+i*3+1)+1,*(Normindices+i*3+1)+1,*(Vertindices+i*3+2)+1,*(UVindices+i*3+2)+1,*(Normindices+i*3+2)+1);
			}
		}
		fclose(fpwrite);

	}
}