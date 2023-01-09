import scala.io.Source
import scala.collection.mutable

object Day19:

  def parseRule(line: String): (Int, Any) =
    val tokens = line.split("[: \"]").toList
    val id = tokens.head.toInt
    if line.contains("\"") then (id, tokens(3))
    else
      val split = tokens.indexOf("|")
      if split == -1 then (id, tokens.drop(2).map(_.toInt))
      else (id, (tokens.slice(2, split).map(_.toInt), tokens.drop(split + 1).map(_.toInt)))

  private def getConcat(arr: List[Int], rules: Map[Int, Any], validSets: mutable.Map[Int, Set[String]]): Set[String] =
    arr.foldLeft(Set(""))((cur: Set[String], j: Int) => {
      for
        x <- cur
        y <- calc(j, rules, validSets)
      yield x + y
    })

  def calc(i: Int, rules: Map[Int, Any], validSets: mutable.Map[Int, Set[String]]): Set[String] =
    validSets.getOrElseUpdate(i, rules(i) match
      case s: String => Set(s)
      case arr: List[Int] => getConcat(arr, rules, validSets)
      case (a: List[Int], b: List[Int]) => getConcat(a, rules, validSets).union(getConcat(b, rules, validSets)))

  private def matching(line: String, valid42: Set[String]): Boolean =
    val parts = line.grouped(8).toVector
    val i = parts.indexWhere(!valid42.contains(_))
    2 * i > parts.length && i < parts.length && parts.drop(i).forall(!valid42.contains(_))

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day19.txt").mkString
    val groups = lines.split("\n\n")
    val rules = Map.from(groups(0).split("\n").map(parseRule))
    val validSets: mutable.Map[Int, Set[String]] = mutable.Map.empty
    val valid42 = calc(42, rules, validSets)
    println(groups(1).split("\n").count(matching(_, valid42)))