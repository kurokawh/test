CREATE TABLE IF NOT EXISTS wordcount(
  word TEXT PRIMARY KEY,
  cnt INTEGER
) WITHOUT ROWID;

CREATE TABLE IF NOT EXISTS old_wordcount(
  word TEXT PRIMARY KEY,
  cnt INTEGER
);

SELECT cnt FROM wordcount WHERE word="xx";
SELECT cnt FROM wordcount WHERE word='xyzzy';

