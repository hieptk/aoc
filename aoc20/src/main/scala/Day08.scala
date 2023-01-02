import scala.annotation.tailrec
import scala.io.Source

object Day08:

  @tailrec
  private def doit(i: Int, acc: Int, lines: Vector[(String, Int)], seen: Set[Int]): (Boolean, Int) =
    if i >= lines.size then return (true, acc)
    if seen.contains(i) then return (false, acc)
    lines(i)._1 match
      case "acc" => doit(i + 1, acc + lines(i)._2, lines, seen + i)
      case "jmp" => doit(i + lines(i)._2, acc, lines, seen + i)
      case "nop" => doit(i + 1, acc, lines, seen + i)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day08.txt").getLines().map(line => {
      val tokens = line.split(" ")
      (tokens(0), tokens(1).toInt)
    }).toVector
    println(doit(0, 0, lines, Set.empty))

    lines.indices.foreach(i => {
      val (op, v) = lines(i)
      if op != "acc" then
        val newop = if op == "jmp" then "nop" else "jmp"
        val res = doit(0, 0, lines.updated(i, (newop, v)), Set.empty)
        if res._1 then
          print(res)
          sys.exit(0)
    })