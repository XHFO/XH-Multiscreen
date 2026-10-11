#pragma once
// Display-owned UI helpers; generic C6 remains an exact no-op.
static const char *local_label(const char *text){
#if C6_FORMLABS_ONLY
    return c6_renderer_localized(renderer(),text);
#else
    return text;
#endif
}
static const char *local_format(const char *zh,const char *en){
#if C6_FORMLABS_ONLY
    if(standalone_config.language==1)return en;
#else
    (void)en;
#endif
    return zh;
}
