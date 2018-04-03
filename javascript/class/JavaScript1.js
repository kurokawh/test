// https://html5experts.jp/takazudo/17355/

/* Animalクラス */
class Animal {
    constructor(name) {
        this.name = name;
    }
    set name(name) {
        this._name = name;
    }
    get name() {
        return this._name;
    }
    walk() {
        console.log(this.name + 'が歩いてます');
    }
}


/* Catクラス */
class Cat extends Animal {
    constructor(name, color) {
        super(name); // Animalクラスのconstructor呼び出し
        this.color = color;
    }
    get color() {
        return this._color;
    }
    set color(color) {
        this._color = color;
    }
    mew() {
        console.log(this.color + '色の' + this.name + 'がニャーと鳴いてます');
    }
    walk() {
        super.walk(); // Animalクラスのwalkメソッド呼び出し
        console.log('忍び足です');
    }
}

module.exports = Cat;