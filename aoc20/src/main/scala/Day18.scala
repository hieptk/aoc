import scala.annotation.tailrec
import scala.collection.immutable.Queue
import scala.io.Source

object Day18:

  private val numRegex = "(\\d+)".r
  private val calc: Map[String, (Long, Long) => Long] = Map(
    "+" -> ((a, b) => a + b),
    "*" -> ((a, b) => a * b)
  )

  private def calcHead(res: List[Long], op: String): List[Long] =
    calc(op)(res.head, res(1)) +: res.drop(2)

  @tailrec
  private def eval(res: List[Long], ops: List[String], tokens: Array[String],
                   precedence: Map[String, Int]): Long =
    if tokens.isEmpty then
      if ops.isEmpty then res.head
      else eval(calcHead(res, ops.head), ops.tail, tokens, precedence)
    else
      tokens.head match
        case numRegex(num) => eval(num.toLong +: res, ops, tokens.tail, precedence)
        case "(" => eval(res, tokens.head +: ops, tokens.tail, precedence)
        case ")" =>
          if ops.head.equals("(") then eval(res, ops.tail, tokens.tail, precedence)
          else eval(calcHead(res, ops.head), ops.tail, tokens, precedence)
        case _ =>
          if ops.isEmpty || ops.head.equals("(") || precedence(ops.head) < precedence(tokens.head) then
            eval(res, tokens.head +: ops, tokens.tail, precedence)
          else eval(calcHead(res, ops.head), ops.tail, tokens, precedence)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day18.txt").getLines()
    val tokens = lines.map(line => {
      line.replace("(", "( ").replace(")", " )").split(" ")
    }).toList
    println(tokens.map(t => eval(List.empty, List.empty, t, Map("*" -> 0, "+" -> 0))).sum)
    println(tokens.map(t => eval(List.empty, List.empty, t, Map("*" -> 0, "+" -> 1))).sum)