./gen > data/0.in
./ac < data/0.in > data/0a.out
./kmp < data/0.in > data/0k.out
./trie < data/0.in > data/0t.out
diff data/0a.out data/0k.out
diff data/0a.out data/0t.out