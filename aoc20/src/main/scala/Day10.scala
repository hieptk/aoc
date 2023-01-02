import scala.annotation.tailrec
import scala.io.Source

object Day10:

  @tailrec
  private def dp(i: Int, f: Vector[Long], sorted: Vector[Int]): Long =
    var res = 0L
    var j = i - 1
    while j >= 0 && sorted(j) >= sorted(i) - 3 do
      res = res + f(j)
      j = j - 1
    if i == sorted.size - 1 then res
    else dp(i + 1, f :+ res, sorted)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day10.txt").getLines().map(_.toInt).toVector
    val sorted = 0 +: lines.sorted :+ lines.max + 3
    val cnt = sorted.sliding(2).map(a => a(1) - a(0)).toVector.groupBy(identity)
    println(cnt(1).size * cnt(3).size)
    println(dp(1, Vector(1), sorted))