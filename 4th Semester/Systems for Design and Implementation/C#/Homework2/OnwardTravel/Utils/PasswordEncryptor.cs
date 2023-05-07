using System.Security.Cryptography;
using System.Text;

namespace OnwardTravel.Utils
{
    internal static class PasswordEncryptor
    {
        public static string Encrypt(string password)
        {
            SHA256 sha256 = SHA256.Create();
            byte[] bytes = Encoding.UTF8.GetBytes(password);
            byte[] hash = sha256.ComputeHash(bytes);
            return Convert.ToBase64String(hash);
        }
    }
}
