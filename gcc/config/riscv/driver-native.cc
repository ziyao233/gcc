#define IN_TARGET_CODE 1

#define INCLUDE_STRING
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "riscv-subset.h"

#define STRINGIFY__(x) #x
#define STRINGIFY(x) STRINGIFY__(x)

// todo: let's define the function on Linux only.

#if defined(__linux__)

#define __NR_riscv_hwprobe 258
#define RISCV_HWPROBE_KEY_MVENDORID 0
#define RISCV_HWPROBE_KEY_MARCHID 1
#define RISCV_HWPROBE_KEY_MIMPID 2
#define RISCV_HWPROBE_KEY_BASE_BEHAVIOR 3
#define RISCV_HWPROBE_BASE_BEHAVIOR_IMA (1ULL << 0)
#define RISCV_HWPROBE_KEY_IMA_EXT_0 4
#define RISCV_HWPROBE_IMA_FD (1ULL << 0)
#define RISCV_HWPROBE_IMA_C (1ULL << 1)
#define RISCV_HWPROBE_IMA_V (1ULL << 2)
#define RISCV_HWPROBE_EXT_ZBA (1ULL << 3)
#define RISCV_HWPROBE_EXT_ZBB (1ULL << 4)
#define RISCV_HWPROBE_EXT_ZBS (1ULL << 5)
#define RISCV_HWPROBE_EXT_ZICBOZ (1ULL << 6)
#define RISCV_HWPROBE_EXT_ZBC (1ULL << 7)
#define RISCV_HWPROBE_EXT_ZBKB (1ULL << 8)
#define RISCV_HWPROBE_EXT_ZBKC (1ULL << 9)
#define RISCV_HWPROBE_EXT_ZBKX (1ULL << 10)
#define RISCV_HWPROBE_EXT_ZKND (1ULL << 11)
#define RISCV_HWPROBE_EXT_ZKNE (1ULL << 12)
#define RISCV_HWPROBE_EXT_ZKNH (1ULL << 13)
#define RISCV_HWPROBE_EXT_ZKSED (1ULL << 14)
#define RISCV_HWPROBE_EXT_ZKSH (1ULL << 15)
#define RISCV_HWPROBE_EXT_ZKT (1ULL << 16)
#define RISCV_HWPROBE_EXT_ZVBB (1ULL << 17)
#define RISCV_HWPROBE_EXT_ZVBC (1ULL << 18)
#define RISCV_HWPROBE_EXT_ZVKB (1ULL << 19)
#define RISCV_HWPROBE_EXT_ZVKG (1ULL << 20)
#define RISCV_HWPROBE_EXT_ZVKNED (1ULL << 21)
#define RISCV_HWPROBE_EXT_ZVKNHA (1ULL << 22)
#define RISCV_HWPROBE_EXT_ZVKNHB (1ULL << 23)
#define RISCV_HWPROBE_EXT_ZVKSED (1ULL << 24)
#define RISCV_HWPROBE_EXT_ZVKSH (1ULL << 25)
#define RISCV_HWPROBE_EXT_ZVKT (1ULL << 26)
#define RISCV_HWPROBE_EXT_ZFH (1ULL << 27)
#define RISCV_HWPROBE_EXT_ZFHMIN (1ULL << 28)
#define RISCV_HWPROBE_EXT_ZIHINTNTL (1ULL << 29)
#define RISCV_HWPROBE_EXT_ZVFH (1ULL << 30)
#define RISCV_HWPROBE_EXT_ZVFHMIN (1ULL << 31)
#define RISCV_HWPROBE_EXT_ZFA (1ULL << 32)
#define RISCV_HWPROBE_EXT_ZTSO (1ULL << 33)
#define RISCV_HWPROBE_EXT_ZACAS (1ULL << 34)
#define RISCV_HWPROBE_EXT_ZICOND (1ULL << 35)
#define RISCV_HWPROBE_EXT_ZIHINTPAUSE (1ULL << 36)
#define RISCV_HWPROBE_EXT_ZVE32X (1ULL << 37)
#define RISCV_HWPROBE_EXT_ZVE32F (1ULL << 38)
#define RISCV_HWPROBE_EXT_ZVE64X (1ULL << 39)
#define RISCV_HWPROBE_EXT_ZVE64F (1ULL << 40)
#define RISCV_HWPROBE_EXT_ZVE64D (1ULL << 41)
#define RISCV_HWPROBE_EXT_ZIMOP  (1ULL << 42)
#define RISCV_HWPROBE_EXT_ZCA    (1ULL << 43)
#define RISCV_HWPROBE_EXT_ZCB    (1ULL << 44)
#define RISCV_HWPROBE_EXT_ZCD    (1ULL << 45)
#define RISCV_HWPROBE_EXT_ZCF    (1ULL << 46)
#define RISCV_HWPROBE_EXT_ZCMOP  (1ULL << 47)
#define RISCV_HWPROBE_EXT_ZAWRS  (1ULL << 48)
#define RISCV_HWPROBE_KEY_CPUPERF_0 5
#define RISCV_HWPROBE_MISALIGNED_UNKNOWN (0 << 0)
#define RISCV_HWPROBE_MISALIGNED_EMULATED (1ULL << 0)
#define RISCV_HWPROBE_MISALIGNED_SLOW (2 << 0)
#define RISCV_HWPROBE_MISALIGNED_FAST (3 << 0)
#define RISCV_HWPROBE_MISALIGNED_UNSUPPORTED (4 << 0)
#define RISCV_HWPROBE_MISALIGNED_MASK (7 << 0)
#define RISCV_HWPROBE_KEY_ZICBOZ_BLOCK_SIZE 6

struct riscv_hwprobe {
  long long key;
  unsigned long long value;
};

struct riscv_hwprobe_ext_bitmask_t {
  const char *ext;
  int bit_pos;
};

const struct riscv_hwprobe_ext_bitmask_t hwprobe_ima_ext0_bitmask_table[] = {
  { "f",		0 },
  { "d",		0 },
  { "c",		1 },
  { "v",		2 },
  { "zba",		3 },
  { "zbb",		4 },
  { "zbs",		5 },
  { "zicboz",		6 },
  { "zbc",		7 },
  { "zbkb",		8 },
  { "zbkc",		9 },
  { "zbkx",		10 },
  { "zknd",		11 },
  { "zkne",		12 },
  { "zknh",		13 },
  { "zksed",		14 },
  { "zksh",		15 },
  { "zkt",		16 },
  { "zvbb",		17 },
  { "zvbc",		18 },
  { "zvkb",		19 },
  { "zvkg",		20 },
  { "zvkned",		21 },
  { "zvknha",		22 },
  { "zvknhb",		23 },
  { "zvksed",		24 },
  { "zvksh",		25 },
  { "zvkt",		26 },
  { "zfh",		27 },
  { "zfhmin",		28 },
  { "zihintntl",	29 },
  { "zvfh",		30 },
  { "zvfhmin",		31 },
  { "zfa",		32 },
  { "ztso",		33 },
  { "zacas",		34 },
  { "zicond",		35 },
  { "zihintpause",	36 },
  { "zve32x",		37 },
  { "zve32f",		38 },
  { "zve64x",		39 },
  { "zve64f",		40 },
  { "zve64d",		41 },
  { "zimop",		42 },
  { "zca",		43 },
  { "zcb",		44 },
  { "zcd",		45 },
  { "zcf",		46 },
  { "zcmop",		47 },
  { "zawrs",		48 },
};

static long
syscall_5_args (long nr, long arg1, long arg2, long arg3, long arg4, long arg5)
{
  register long a7 __asm__ ("a7") = nr;
  register long a0 __asm__ ("a0") = arg1;
  register long a1 __asm__ ("a1") = arg2;
  register long a2 __asm__ ("a2") = arg3;
  register long a3 __asm__ ("a3") = arg4;
  register long a4 __asm__ ("a4") = arg5;
  __asm__ __volatile__ ("ecall\n\t"
			: "=r"(a0)
			: "r"(a7), "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4)
			: "memory");
  return a0;
}

const char *
host_detect_local_cpu (int argc, const char **argv)
{
  gcc_assert (argc == 1);
  gcc_assert (!strcmp (argv[0], "arch"));

  struct riscv_hwprobe hwprobes[] = {
    { RISCV_HWPROBE_KEY_BASE_BEHAVIOR, 0 },
    { RISCV_HWPROBE_KEY_IMA_EXT_0, 0 },
  };

  int ret = syscall_5_args (__NR_riscv_hwprobe, (long)hwprobes,
			    ARRAY_SIZE (hwprobes), 0, 0, 0);
  bool arch_info_available = true;

  const char *base_isa_str;

  if (!ret && (hwprobes[0].value & RISCV_HWPROBE_BASE_BEHAVIOR_IMA))
    base_isa_str = "rv" STRINGIFY (__riscv_xlen) "ima";
  else
    {
      base_isa_str = STRINGIFY (TARGET_RISCV_DEFAULT_ARCH);
      arch_info_available = false;
    }

  riscv_subset_list *ext_list;
  ext_list = riscv_subset_list::parse (base_isa_str, UNKNOWN_LOCATION);

  if (arch_info_available)
    {
      for (unsigned long i = 0;
	   i < ARRAY_SIZE (hwprobe_ima_ext0_bitmask_table);
	   i++)
	{
	  const riscv_hwprobe_ext_bitmask_t *p;
	  p = &hwprobe_ima_ext0_bitmask_table[i];

	  if (hwprobes[1].value & (1ULL << (p->bit_pos))) {
	    ext_list->add (p->ext, true);
	  }
	}
    }

  char *arch_str = xasprintf ("-march=%s", ext_list->to_string (false).c_str());
  delete ext_list;
  return arch_str;
}
#endif /* ! __linux__ */
