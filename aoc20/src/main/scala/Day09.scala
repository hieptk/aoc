import scala.annotation.tailrec
import scala.io.Source

object Day09:

  @tailrec
  private def part1(i: Int, lines: Vector[Long]): Long =
    val allsums = lines.slice(i, i + 25).combinations(2).map(_.sum).toSet
    if !allsums.contains(lines(i + 25)) then lines(i + 25)
    else part1(i + 1, lines)

  @tailrec
  private def part2(i: Int, cur: Long, prefix: Map[Long, Int], s: Long, lines: Vector[Long]): Long =
    if prefix.contains(cur - s) then
      val res = lines.slice(prefix(cur - s), i + 1)
      res.max + res.min
    else part2(i + 1, cur + lines(i + 1), prefix + (cur -> (i + 1)), s, lines)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day09.txt").getLines().map(_.toLong).toVector
    val s = part1(0, lines)
    println(s)
    println(part2(0, lines(0), Map(0L -> 0), s, lines))