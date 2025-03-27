#ifndef _APP_PAGE_H
#define _APP_PAGE_H
#include "SysApp/AppParam.h"


void app_LcdDispDelayHandle( void );
void app_DispPage( SysParam_t *p_SysParamHandle, ePageIDType page_id);

void app_PageEvent_Handle( SysParam_t *p_SysParamHandle );
void app_KeyEvent_Handle( SysParam_t * p_SysParamHandle );
void app_IDCardEvent_Handle( SysParam_t * p_SysParamHandle );
void app_FingerPrintEvent_Handle( SysParam_t * p_SysParamHandle );
void app_GizwitsDataEvent_Handle( SysParam_t * p_SysParamHandle );


#endif /* _APP_PAGE_H */

