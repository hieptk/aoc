import scala.annotation.tailrec
import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer
import scala.io.Source

object Day16:

  type Rule = (String, Int, Int, Int, Int)
  private val rulePattern = "([a-z ]+): (\\d+)-(\\d+) or (\\d+)-(\\d+)".r

  private def parseRule(line: String): Rule =
    rulePattern.findFirstMatchIn(line).map(m => {
      (m.group(1), m.group(2).toInt, m.group(3).toInt, m.group(4).toInt, m.group(5).toInt)
    }).get

  private def parseTicket(line: String): Array[Int] =
    line.split(",").map(_.toInt)

  private def isInvalid(num: Int, rules: Array[Rule]): Boolean =
    rules.forall((_, l1, r1, l2, r2) => (num < l1 || num > r1) && (num < l2 || num > r2))

  private def matchRule(col: Array[Int], rule: Rule): Boolean =
    val(_, l1, r1, l2, r2) = rule
    col.forall(num => (num >= l1 && num <= r1) || (num >= l2 && num <= r2))

  @tailrec
  private def traceBack(mask: Int, rule2Col: Vector[Int], dp: ArrayBuffer[Int]): Vector[Int] =
    if mask == 0 then rule2Col
    else traceBack(mask & (~(1 << dp(mask))), rule2Col.updated(dp(mask), Integer.bitCount(mask) - 1), dp)

  def main(args: Array[String]): Unit =
    val lines = Source.fromResource("day16.txt").mkString
    val groups = lines.split("\n\n")
    val rules = groups(0).split("\n").map(parseRule)
    val nearbyTickets = groups(2).split("\n").tail.map(parseTicket)
    println(nearbyTickets.flatten.filter(isInvalid(_, rules)).sum)

    val myTicket = parseTicket(groups(1).split("\n")(1))
    val validTickets = nearbyTickets.filter(_.forall(!isInvalid(_, rules))).prepended(myTicket)
    val n = rules.length
    val colMatchRule = Vector.tabulate(n)(i => {
      val col = validTickets.map(ticket => ticket(i))
      Vector.tabulate(n)(j => matchRule(col, rules(j)))
    })

    val dp = ArrayBuffer.fill(1 << n)(-1)
    (0 until n).filter(colMatchRule(0)(_)).foreach(i => dp(1 << i) = i)
    for
      mask <- 1 until (1 << n) - 1
      i = Integer.bitCount(mask)
      if dp(mask) != -1
      next <- 0 until n
      if ((mask >> next) & 1) == 0 && colMatchRule(i)(next)
    do
      dp(mask | (1 << next)) = next

    val rule2col = traceBack((1 << n) - 1, Vector.fill(n)(-1), dp)
    val departureRules = rules.zip(rule2col).filter((rule, _) => rule._1.startsWith("departure"))
    println(departureRules.map((_, col) => myTicket(col).toLong).product)