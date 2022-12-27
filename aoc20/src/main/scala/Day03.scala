import scala.io.Source

object Day03:
  private val slopes = Vector((1, 1), (3, 1), (5, 1), (7, 1), (1, 2))

  private def isTree(line: String, i: Int, slope: (Int, Int)): Boolean =
    i % slope(1) == 0 && line.charAt((i / slope(1) * slope(0)) % line.length) == '#'

  private def count(lines: Seq[String], slope: (Int, Int)): Long =
    lines.zipWithIndex.count((line, i) => isTree(line, i, slope))


  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day03.txt").getLines().toSeq
    println(count(lines, slopes(1)))
    println(slopes.map(slope => count(lines, slope)).product)