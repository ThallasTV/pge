

#if !defined (_SWholeIO_H)
#   define _SWholeIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_SWholeIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

EXTERN void SWholeIO_ReadInt (int *int_);
EXTERN void SWholeIO_WriteInt (int int_, unsigned int width);
EXTERN void SWholeIO_ReadCard (unsigned int *card);
EXTERN void SWholeIO_WriteCard (unsigned int card, unsigned int width);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
