splot "Omega".i.".txt" matrix with lines title sprintf("t=%i",i)
i=i+1
if (i <= n) reread
