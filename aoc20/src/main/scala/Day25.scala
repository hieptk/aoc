import scala.annotation.tailrec
import scala.io.Source

object Day25:

  private val mod = 20201227L

  @tailrec
  private def decrypt(x: Long, y: Long, acc: Long, acc2: Long): Long =
    if x == acc then acc2
    else decrypt(x, y, (acc * 7L) % mod, (acc2 * y) % mod)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day25.txt").getLines().toVector
    println(decrypt(lines(0).toLong, lines(1).toLong, 1L, 1L))