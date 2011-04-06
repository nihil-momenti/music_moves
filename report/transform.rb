#!/usr/bin/env ruby

at_end = false

while gets
  case $_
  when /\\begin\{quote\}\\begin\{lstlisting\}/
    puts "\\begin{lstlisting}"
  when /\\end\{lstlisting\}/
    puts $_
    at_end = true
  when /\\end\{quote\}/
    puts $_ unless at_end
    at_end = false
  else
    puts $_
  end
end
