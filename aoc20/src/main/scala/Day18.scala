import scala.annotation.tailrec
import scala.collection.immutable.Queue
import scala.io.Source

object Day18:

  private val numRegex = "(\\d+)".r

  @tailrec
  private def convertToRPN(res: Queue[Any], ops: List[String], tokens: Array[String],
                           precedence: Map[String, Int]): Queue[Any] =
    if tokens.isEmpty then res ++ ops
    else
      tokens.head match
        case numRegex(num) => convertToRPN(res :+ num.toLong, ops, tokens.tail, precedence)
        case "(" => convertToRPN(res, tokens.head +: ops, tokens.tail, precedence)
        case ")" =>
          if ops.head.equals("(") then convertToRPN(res, ops.tail, tokens.tail, precedence)
          else convertToRPN(res :+ ops.head, ops.tail, tokens, precedence)
        case _ =>
          if ops.isEmpty || ops.head.equals("(") || precedence(ops.head) < precedence(tokens.head) then
            convertToRPN(res, tokens.head +: ops, tokens.tail, precedence)
          else convertToRPN(res :+ ops.head, ops.tail, tokens, precedence)

  @tailrec
  private def evalRPN(nums: List[Long], tokens: Queue[Any]): Long =
    if tokens.isEmpty then nums.product
    else
      tokens.head match
        case num: Long => evalRPN(num +: nums, tokens.tail)
        case "+" => evalRPN((nums.head + nums.tail.head) +: nums.tail.tail, tokens.tail)
        case "*" => evalRPN((nums.head * nums.tail.head) +: nums.tail.tail, tokens.tail)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day18.txt").getLines()
    val tokens = lines.map(line => {
      line.replace("(", "( ").replace(")", " )").split(" ")
    }).toList
    println(tokens.map(t => {
      val rpn = convertToRPN(Queue.empty, List.empty, t, Map("*" -> 0, "+" -> 0))
      evalRPN(List.empty, rpn)
    }).sum)
    println(tokens.map(t => {
      val rpn = convertToRPN(Queue.empty, List.empty, t, Map("*" -> 0, "+" -> 1))
      evalRPN(List.empty, rpn)
    }).sum)