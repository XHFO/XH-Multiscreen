#pragma once
#include "standalone.h"
#include <string.h>

// Match a feature/physical device, never its editable display name. A disabled
// native card does not replace a Mac card; diagnostics != Mac system monitor.
static int c6_hybrid_target(const standalone_config_t *c,const char *kind,const char *serial,const char *brand,const char *source){
    if(!c->enabled||!c->local_first)return -1;
    if(!strcmp(kind,"clock"))return c->clock&&(c->card_mask&1)?0:-1;
    if(!strcmp(kind,"weather"))return c->weather&&(c->card_mask&4)?2:-1;
    if(!strcmp(kind,"ha"))return c->ha_enabled&&c->entity_count&&(c->card_mask&8)?10:-1;
    if(strcmp(kind,"printer")||!*serial||!*brand||!*source)return -1;
    int found=-1;
    for(unsigned i=0;i<c->printer_count;i++){
        const c6_printer_config_t *p=&c->printers[i];
        if(p->enabled&&p->rotate&&!strcmp(p->serial,serial)&&!strcmp(c6_printer_brand(p),brand)&&!strcmp(c6_printer_source(p),source)){
            if(found>=0)return -1;
            found=20+(int)i;
        }
    }
    return found;
}
