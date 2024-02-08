import DefaultOverlay from "../overlay/overlay";
import LoginForm from "./loginForm";

const LoginPage = () => {
  return (
    <DefaultOverlay title={"Login"}>
      <LoginForm />
    </DefaultOverlay>
  );
};

export default LoginPage;
