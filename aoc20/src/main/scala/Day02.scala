import scala.io.Source

object Day02:
  private case class Password(min: Int, max: Int, char: Char, password: String):
    def isValid: Boolean =
      val cnt = password.count(_ == char)
      cnt >= min && cnt <= max

    def isValid2: Boolean =
      password.charAt(min - 1) == char ^ password.charAt(max - 1) == char

  private def parse(line: String): Password =
    val tokens = line.split("[- :]")
    Password(tokens(0).toInt, tokens(1).toInt, tokens(2).charAt(0), tokens(4))

  def main(args: Array[String]): Unit =
    val passwords = Source.fromResource("day02.txt").getLines().map(parse).toSeq
    println(passwords.count(_.isValid))
    println(passwords.count(_.isValid2))