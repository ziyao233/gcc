# Generate $objdir/gcn-device-macros.h from gcn-devices.def
#
# Copyright (C) 2024 Free Software Foundation, Inc.
#
# This file is part of GCC.
#
# GCC is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GCC is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GCC; see the file COPYING3.  If not see
# <http://www.gnu.org/licenses/>.

BEGIN {
  FS= "[(,] *"

  print "/* Generated by gen-gcn-device-macros.awk from gcn-devices.def."
  print "   Do not edit.  */"

  list=""
}

/^GCN_DEVICE\(/ {
  gfx=$2
  list=(list " OPT_" gfx)

  print ""
  next
}

/XNACK default.*HSACO_ATTR_UNSUPPORTED/ {
  printf "\n#define XNACK_%s \"march=%s:;\"", gfx, gfx
  next
}

/XNACK default.*HSACO_ATTR_OFF/ {
  printf "\n#define XNACK_%s \"march=%s:%{!mxnack*|mxnack=default|mxnack=off:-mattr=-xnack;mxnack=on:-mattr=+xnack};\"", gfx, gfx
  next
}

/XNACK default.*HSACO_ATTR_ANY/ {
  printf "\n#define XNACK_%s \"march=%s:%{mxnack=off:-mattr=-xnack;mxnack=on:-mattr=+xnack};\"", gfx, gfx
  next
}

/XNACK default.*HSACO/ {
  print FILENAME ":" NR ": error: unhandled HSACO default at line (gen-gcn-device-macros.awk)" > "/dev/stderr"
  exit 1
}

/SRAM_ECC default.*HSACO_ATTR_UNSUPPORTED/ {
  printf "\n#define SRAM_%s \"march=%s:;\"", gfx, gfx
  next
}

/SRAM_ECC default.*HSACO_ATTR_ANY/ {
  printf "\n#define SRAM_%s \"march=%s:%{msram-ecc=on:-mattr=+sramecc;msram-ecc=off:-mattr=-sramecc};\"", gfx, gfx
  next
}

/SRAM_ECC default.*HSACO/ {
  print FILENAME ":" NR ": error: unhandled HSACO default at line (gen-gcn-device-macros.awk)" > "/dev/stderr"
  exit 1
}

/WAVE64 mode.*HSACO_ATTR_UNSUPPORTED/ {
  printf "\n#define WAVE64_%s \"march=%s:;\"", gfx, gfx
  next
}

/WAVE64 mode.*HSACO_ATTR_ON/ {
  printf "\n#define WAVE64_%s \"march=%s:-mattr=+wavefrontsize64;\"", gfx, gfx
  next
}

/WAVE64 mode.*HSACO/ {
  print FILENAME ":" NR ": error: unhandled HSACO default at line (gen-gcn-device-macros.awk)" > "/dev/stderr"
  exit 1
}

/CU mode.*HSACO_ATTR_UNSUPPORTED/ {
  printf "\n#define CU_%s \"march=%s:;\"", gfx, gfx
  next
}

/CU mode.*HSACO_ATTR_ON/ {
  printf "\n#define CU_%s \"march=%s:-mattr=+cumode;\"", gfx, gfx
  next
}

/CU mode.*HSACO/ {
  print FILENAME ":" NR ": error: unhandled HSACO default at line (gen-gcn-device-macros.awk)" > "/dev/stderr"
  exit 1
}

END {
  print ""
  print ""
  printf "#define XNACKOPT \"%%{\"%s \":%%eexpected march\\n} \"\n", gensub (/OPT/, "XNACK", "g", list)
  printf "#define SRAMOPT \"%%{\"%s \":%%eexpected march\\n} \"\n", gensub (/OPT/, "SRAM", "g", list)
  printf "#define WAVE64OPT \"%%{\"%s \":%%eexpected march\\n} \"\n", gensub (/OPT/, "WAVE64", "g", list)
  printf "#define CUMODEOPT \"%%{\"%s \":%%eexpected march\\n} \"\n", gensub (/OPT/, "CU", "g", list)
}
