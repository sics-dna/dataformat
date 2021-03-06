 /*
 --------------------------------------------------------------------------
 Copyright (C) 1996, 2012, 2015 Anders Holst <aho@sics.se> 

 This code is free software: you can redistribute it and/or modify it
 under the terms of the GNU Lesser General Public License as published
 by the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this code.  If not, see <http://www.gnu.org/licenses/>.
 --------------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include "readtokens.hh"
#include "format.hh"
#include "formatbinary.hh"

/*
class FormatSpecBinary : public FormatSpec {
public:
  FormatSpecBinary(const char* nm = 0) : FormatSpec(nm) {};
  virtual FormatSpec* copy() { FormatSpecBinary* fs = new FormatSpecBinary(name); fs->unset = unset; return fs; };
  virtual void init(struct TokenLink* tok);
  virtual void add(const char* str);
  virtual void save(FILE* f);
  virtual intfloat interpret(const char* str);
  virtual const char* represent(intfloat v);
  virtual int type() { return FORMATSPEC_BINARY; };
};
*/

void FormatSpecBinary::init(struct TokenLink* tok)
{
  name = stripname(tok);
  if (tok->next)
    fprintf(stderr, "Too many binary format arguments: %s ...\n", tok->token);
}

void FormatSpecBinary::save(FILE* f)
{
  printname(f);
  fprintf(f, "binary:\n");
}

void FormatSpecBinary::add(const char* str)
{
  float val;
  if (is_unknown(str)) 
    ;
  else if (!is_cont(str) || ((val = get_cont(str)) < 0.0) || (val > 1.0))
    fprintf(stderr, "Bad binary value: %s\n", str);
}

intfloat FormatSpecBinary::interpret(const char* str)
{
  intfloat res;
  if (is_unknown(str))
    res.i = -1;
  else if (is_cont(str))
    res.f = get_cont(str);
  else {
    res.i = -1;
    fprintf(stderr, "Bad binary value: %s\n", str);
  }
  return res;
}

const char* FormatSpecBinary::represent(intfloat v)
{
  static char buf[12];
  if (v.i == -1)
    return "?";
  else
    return sprintf(buf, "%.5f", v.f), buf;
}
