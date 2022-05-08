#include <hls_video.h>
#include <stdint.h>

void conv(uint8_t image_in[320*240],uint8_t image_out[320*240])
{
#pragma HLS INTERFACE m_axi depth=76800 port=image_out offset=slave bundle=CRTL
#pragma HLS INTERFACE m_axi depth=76800 port=image_in offset=slave bundle=CRTL
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL
#pragma HLS DATAFLOW
	const char coeff[3][3]={{-1,-2,-1},{0,0,0},{1,2,1}};
	hls::Mat<320,240,HLS_8UC1> src;
	hls::Mat<320,240,HLS_8UC1> dst;
    hls::AXIM2Mat<240,uint8_t,320,240,HLS_8UC1>(image_in,src);
    hls::Window<3,3,char> kernel;
    for(int i=0;i<3;i++)
    {
    	for(int j=0;j<3;j++)
    	{
    		kernel.val[i][j]=coeff[i][j];
    	}
    }
    hls::Point_<int> anchor =hls::Point_<int>(-1,-1);
    hls::Filter2D(src,dst,kernel,anchor);
    hls::Mat2AXIM<240,uint8_t,320,240,HLS_8UC1>(dst,image_out);
}
