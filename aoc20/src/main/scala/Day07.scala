import java.util.regex.Pattern
import scala.collection.mutable.ArrayBuffer
import scala.collection.mutable
import scala.io.Source

object Day07:

  private val id: mutable.Map[String, Int] = mutable.Map.empty
  private val adj: ArrayBuffer[ArrayBuffer[(Int, Int)]] = ArrayBuffer.empty
  private val adj2: ArrayBuffer[ArrayBuffer[(Int, Int)]] = ArrayBuffer.empty
  private val visited: ArrayBuffer[Boolean] = ArrayBuffer.empty
  private val sum: ArrayBuffer[Int] = ArrayBuffer.empty

  private def getId(name: String): Int =
    id.getOrElseUpdate(name, {
      adj.addOne(ArrayBuffer.empty)
      adj2.addOne(ArrayBuffer.empty)
      visited.addOne(false)
      sum.addOne(-1)
      id.size
    })

  def parse(lines: Seq[String]): Unit =
    val pattern = "(\\d+) ([^,.]*) bags?[,.] ?".r
    lines.foreach(line => {
      val parts = line.split(" bags contain ")
      val node = getId(parts(0))
      pattern.findAllMatchIn(parts(1)).foreach(m => {
        val w = m.group(1).toInt
        val node2 = getId(m.group(2))
        adj(node2).addOne((node, w))
        adj2(node).addOne((node2, w))
      })
    })

  private def dfs(i: Int): Int =
    visited(i) = true
    adj(i).filter((j, _) => !visited(j)).map((j, _) => dfs(j)).sum + 1

  private def dfs2(i: Int): Int =
    if sum(i) != -1 then sum(i)
    else
      sum(i) = adj2(i).map((j, w) => w * dfs2(j)).sum + 1
      sum(i)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day07.txt").getLines().toSeq
    parse(lines)
    println(dfs(id("shiny gold")) - 1)
    println(dfs2(id("shiny gold")) - 1)