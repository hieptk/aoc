import scala.annotation.tailrec
import scala.io.Source

object Day12:

  private val dx = Vector(1, 0, -1, 0)
  private val dy = Vector(0, -1, 0, 1)

  private def move(pos: (Int, Int, Int), step: (Char, Int)): (Int, Int, Int) =
    val (x, y, d) = pos
    step match
      case ('N', s) => (x, y + s, d)
      case ('S', s) => (x, y - s, d)
      case ('E', s) => (x + s, y, d)
      case ('W', s) => (x - s, y, d)
      case ('L', s) => (x, y, (d - (s / 90) + 4) % 4)
      case ('R', s) => (x, y, (d + (s / 90)) % 4)
      case ('F', s) => (x + dx(d) * s, y + dy(d) * s, d)

  private def rotate(x: Int, y: Int, wx: Int, wy: Int, rad: Double): (Int, Int, Int, Int) =
    val wx2 = math.cos(rad) * wx - math.sin(rad) * wy
    val wy2 = math.sin(rad) * wx + math.cos(rad) * wy
    (x, y, wx2.round.toInt, wy2.round.toInt)

  private def move2(pos: (Int, Int, Int, Int), step: (Char, Int)): (Int, Int, Int, Int) =
    val (x, y, wx, wy) = pos
    val res = step match
      case ('N', s) => (x, y, wx, wy + s)
      case ('S', s) => (x, y, wx, wy - s)
      case ('E', s) => (x, y, wx + s, wy)
      case ('W', s) => (x, y, wx - s, wy)
      case ('L', s) => rotate(x, y, wx, wy, s * math.Pi / 180.0)
      case ('R', s) => rotate(x, y, wx, wy, -s * math.Pi / 180.0)
      case ('F', s) => (x + wx * s, y + wy * s, wx, wy)
    res

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day12.txt").getLines()
    val steps = lines.map(line => (line(0), line.substring(1).toInt)).toSeq
    val (x, y, _) = steps.foldLeft((0, 0, 0))((pos, step) => move(pos, step))
    println(x.abs + y.abs)

    val (x2, y2, _, _) = steps.foldLeft((0, 0, 10, 1))((pos, step) => move2(pos, step))
    println(x2.abs + y2.abs)