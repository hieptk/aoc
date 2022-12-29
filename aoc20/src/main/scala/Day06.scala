import scala.io.Source

object Day06:

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day06.txt").mkString
    val groups = lines.split("\n\n")
    println(groups.map(_.replace("\n", "").toSet.size).sum)
    println(groups.map(_.split("\n").reduce(_.intersect(_)).length).sum)