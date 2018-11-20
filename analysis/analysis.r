if(!exists("AllKeyCors", mode="function")) source ("dpa.R")

parseTracesPTxts("traces.csv", "plaintexts.csv", 250100)
keys = 0:255
akcs <- AllKeyCors(plaintexts, keys, traces)
write.csv(akcs, "corrs.csv")

