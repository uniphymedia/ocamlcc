/*************************************************************************/
/*                                                                       */
/*                               OCamlCC                                 */
/*                                                                       */
/*                    Michel Mauny, Benoit Vaugon                        */
/*                          ENSTA ParisTech                              */
/*                                                                       */
/*    This file is distributed under the terms of the CeCILL license.    */
/*    See file ../LICENSE-en.                                            */
/*                                                                       */
/*************************************************************************/

#if defined(OCAMLCC_ARCH_X86) || defined(OCAMLCC_ARCH_X86_64)

#define ocamlcc_dynamic_apply(nargs, cfun_nargs, curr_fsz, next_fsz,    \
                              dst, args...) {                           \
  ocamlcc_apply_init_stack(curr_fsz, next_fsz);                         \
  dst ocamlcc_apply_##nargs(args);                                      \
  ocamlcc_apply_restore_stack(next_fsz);                                \
}

#define ocamlcc_partial_apply(nargs, cfun_nargs, curr_fsz, next_fsz, \
                              dst, args...)                          \
  ocamlcc_dynamic_apply(nargs, cfun_nargs, curr_fsz, next_fsz, dst, args)

#define ocamlcc_static_apply(nargs, cfun_nargs, curr_fsz, next_fsz,     \
                             dst, f, args...) {                         \
  ocamlcc_apply_init_stack(curr_fsz, next_fsz);                         \
  dst f(args);                                                          \
  ocamlcc_apply_restore_stack(next_fsz);                                \
}

#define ocamlcc_static_notc_apply(nargs, cfun_nargs, curr_fsz, next_fsz, \
                                  dst, f, args...)                      \
  ocamlcc_static_apply(nargs, cfun_nargs, curr_fsz, next_fsz, dst, f, args)

/***/

#define ocamlcc_dynamic_standard_appterm(nargs, cfun_nargs, curr_fsz,   \
                                         args...) {                     \
  OffsetSp(0);                                                          \
  return ocamlcc_apply_##nargs(args);                                   \
}

#define ocamlcc_partial_standard_appterm(nargs, cfun_nargs, curr_fsz, \
                                         args...)                     \
  ocamlcc_dynamic_standard_appterm(nargs, cfun_nargs, curr_fsz, args)

#define ocamlcc_static_standard_appterm(nargs, cfun_nargs, f, args...) { \
  OffsetSp(0);                                                          \
  return f(args);                                                       \
}

/***/

#define ocamlcc_dynamic_special_appterm(nargs, cfun_nargs, curr_fsz,    \
                                        args...) {                      \
  OffsetSp(0);                                                          \
  ocamlcc_tail_call_##cfun_nargs((value) &ocamlcc_apply_##nargs, args); \
}

#define ocamlcc_partial_special_appterm(nargs, cfun_nargs, curr_fsz, \
                                        args...)                     \
  ocamlcc_dynamic_special_appterm(nargs, cfun_nargs, curr_fsz, args)

#define ocamlcc_static_special_appterm(nargs, cfun_nargs, f, args...) { \
  OffsetSp(0);                                                          \
  ocamlcc_tail_call_##cfun_nargs((value) &f, args);                     \
}

/***/

#define ocamlcc_special_special_appterm(nargs, cfun_nargs, curr_fsz, \
                                        args...)                     \
  ocamlcc_dynamic_special_appterm(nargs, cfun_nargs, curr_fsz, args)

/***/

#define OCAMLCC_SPECIAL_TAIL_CALL_HEADER(id)

#endif /* OCAMLCC_ARCH_X86 || OCAMLCC_ARCH_X86_64 */
