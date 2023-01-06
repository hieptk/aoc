import scala.io.Source
import scala.collection.mutable

object Day15:

  def doit(lastNum: Int, lastSeen: mutable.Map[Int, Int], i: Int): Int =
    val res = i - 1 - lastSeen.getOrElse(lastNum, i - 1)
    lastSeen(lastNum) = i - 1
    res

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day15.txt").getLines().toVector
    val nums = lines.head.split(",").map(_.toInt).toVector
    val lastSeen = mutable.Map.from(nums.zipWithIndex)
    val lastNum = (nums.length + 1 until 30000000).foldLeft(0)((lastNum, i) => doit(lastNum, lastSeen, i))
    println(lastNum)