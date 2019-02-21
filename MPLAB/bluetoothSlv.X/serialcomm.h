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
#include "serialcomm.h"
#include <GenericTypeDefs.h>
#include <plib.h>
#include <stdio.h>
#include <string.h>
#include <serial.h>
// defines

int UpdateDataBuffer(int uart, int max_size);
void GetDataBuffer(int uart, char *buffer);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif // SERIALCOMM_H

/* *****************************************************************************
 End of File
 */
