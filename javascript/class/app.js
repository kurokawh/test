'use strict';

var Cat = require('./JavaScript1');

console.log('Hello world');



/* Catクラスのインスタンス作成 */
var cat1 = new Cat('タマ', '茶');
console.log(cat1.name); // タマ
cat1.walk(); // タマが歩いてます
// 忍び足です
cat1.mew();  // 茶色のタマがニャーと鳴いてます

var cat2 = new Cat('コタロー', '黒');
console.log(cat2.name); // コタロー
cat2.walk(); // コタローが歩いてます
// 忍び足です
cat2.mew();  // 黒色のコタローがニャーと鳴いてます
