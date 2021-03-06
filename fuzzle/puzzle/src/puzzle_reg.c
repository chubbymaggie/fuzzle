#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <puzzle.h>


/* Create register record */
bool pzl_create_reg_rec(pzl_ctx_t *context, void *usr_reg)
{
    CHECK_PTR(context, "pzl_create_reg_rec - context");
    CHECK_PTR(usr_reg, "pzl_create_reg_rec - user_regs");

    /* Create register record */
    reg_rec_t *reg_rec = (reg_rec_t *) malloc(sizeof(reg_rec_t));
    if(reg_rec == NULL)
    {
        printf("pzl_create_reg_record: register recored cannot be allocated\n");
        return false;
    }
    reg_rec->type = 0x0002;

    /* Allocate and copy user registers */
    switch(context->hdr_rec.arch)
    {
        case X86_64:
            reg_rec->usr_reg = (void *) malloc(sizeof(user_regs_x86_64_t));
            memcpy(reg_rec->usr_reg, usr_reg, sizeof(user_regs_x86_64_t));
            reg_rec->length = (2 + 8 + 8) + sizeof(user_regs_x86_64_t);
            reg_rec->usr_reg_len = sizeof(user_regs_x86_64_t);
            context->reg_rec = reg_rec;
            break;

        default:
            printf("pzl_create_reg_record: processor arch not recognised\n");
            free(reg_rec);
            reg_rec = NULL;
            return false;
    }

    return true;
}
