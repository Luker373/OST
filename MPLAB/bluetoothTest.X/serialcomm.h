/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _SERIALCOMM_H    /* Guard against multiple inclusion */
#define _SERIALCOMM_H

//includes 
#include <xc.h>
#include <GenericTypeDefs.h>
// defines



void initUART1();
void SendDataBufferUART1(const char *buffer, UINT32 size);
UINT32 GetDataBufferUART1(char *buffer, UINT32 max_size);

void initUART2();
void SendDataBufferUART2(const char *buffer, UINT32 size);
UINT32 GetDataBufferUART2(char *buffer, UINT32 max_size);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif // SERIALCOMM_H

/* *****************************************************************************
 End of File
 */
