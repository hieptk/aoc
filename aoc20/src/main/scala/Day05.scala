import scala.io.Source

object Day05:
  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day05.txt").getLines()
    val binaries = lines.map(_.replaceAll("[FL]", "0").replaceAll("[BR]", "1"))
    val nums = binaries.map(Integer.parseInt(_, 2)).toSeq
    println(nums.max)
    println((nums.max + nums.min) * (nums.max - nums.min + 1) / 2 - nums.sum)