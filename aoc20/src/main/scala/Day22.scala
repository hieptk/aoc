import scala.annotation.tailrec
import scala.io.Source

object Day22:

  @tailrec
  private def play(a: Vector[Int], b: Vector[Int]): Vector[Int] =
    if a.isEmpty then b
    else if b.isEmpty then a
    else if a.head > b.head then play(a.tail.appendedAll(List(a.head, b.head)), b.tail)
    else play(a.tail, b.tail.appendedAll(List(b.head, a.head)))

  private def play2(a: Vector[Int], b: Vector[Int], cache: Set[(Vector[Int], Vector[Int])]): (Boolean, Vector[Int]) =
    if b.isEmpty || cache.contains((a, b)) then (true, a)
    else if a.isEmpty then (false, b)
    else if a.head <= a.tail.length && b.head <= b.tail.length then
      val (aWins, _) = play2(a.slice(1, a.head + 1), b.slice(1, b.head + 1), Set.empty)
      if aWins then play2(a.tail.appendedAll(List(a.head, b.head)), b.tail, cache + ((a, b)))
      else play2(a.tail, b.tail.appendedAll(List(b.head, a.head)), cache + ((a, b)))
    else if a.head > b.head then play2(a.tail.appendedAll(List(a.head, b.head)), b.tail, cache + ((a, b)))
    else play2(a.tail, b.tail.appendedAll(List(b.head, a.head)), cache + ((a, b)))

  private def score(a: Vector[Int]) = a.zipWithIndex.map((x, id) => x * (a.length - id)).sum

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day22.txt").mkString
    val groups = lines.split("\n\n")
    val a = groups(0).split("\n").tail.map(_.toInt).toVector
    val b = groups(1).split("\n").tail.map(_.toInt).toVector
    println(score(play(a, b)))
    println(score(play2(a, b, Set.empty)._2))