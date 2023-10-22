//
// Created by dym on 23.10.23.
//

#include <impl.hpp>


namespace pg {


void impl(ImplContext ctx) {
  if (ctx.mode & ImplContext::number) {
    ctx.os_display << 123 << '\n';
  }
  if (ctx.mode & ImplContext::letter) {
    ctx.os_display << "abc\n";
  }
}


}// namespace pg