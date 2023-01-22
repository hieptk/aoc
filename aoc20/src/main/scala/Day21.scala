import scala.io.Source

object Day21:

  def parse(line: String): (Array[String], Array[String]) =
    val id = line.indexOf(" (contains")
    val ingredients = line.substring(0, id).split(" ")
    val allergens = line.substring(id + 11, line.length - 1).split(", ")
    (ingredients, allergens)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day21.txt").getLines()
    val (foodIngs, foodAllergens) = lines.map(parse).toList.unzip
    val ing2foods = foodIngs.zipWithIndex.flatMap((ings, id) => ings.map(ing => (ing, id)))
      .groupMapReduce(_._1)(p => Set(p._2))((a, b) => a.union(b))
    val allergen2foods = foodAllergens.zipWithIndex.flatMap((allergens, id) => allergens.map(a => (a, id)))
      .groupMapReduce(_._1)(p => Set(p._2))((a, b) => a.union(b))
    val ing2allergens = ing2foods.toList.flatMap((ing, foods) => {
      allergen2foods.toList
        .filter((_, foods2) => foods2.subsetOf(foods))
        .map((allergen, _) => (ing, allergen))
    }).groupMapReduce(_._1)(p => Set(p._2))((a, b) => a.union(b))

    println(ing2foods.filter((ing, _) => !ing2allergens.contains(ing)).map(_._2.size).sum)

    val sortedAllergens = allergen2foods.keys.toList.sorted
    val res = ing2allergens.keys.toList.permutations.filter(ings => {
      ings.zip(sortedAllergens).forall((ing, all) => ing2allergens(ing).contains(all))
    }).toList.head
    println(res.mkString(","))