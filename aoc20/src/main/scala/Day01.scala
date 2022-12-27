import scala.io.Source

object Day01:
  def main(args: Array[String]): Unit =
    val nums = Source.fromResource("day01.txt").getLines().map(_.toInt).toSeq
    println(nums.combinations(2).filter(_.sum == 2020).flatten.product)
    println(nums.combinations(3).filter(_.sum == 2020).flatten.product)