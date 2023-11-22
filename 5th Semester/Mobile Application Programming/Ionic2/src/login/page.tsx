import DefaultOverlay from "../overlay";
import LoginForm from "./loginForm";

import styles from "./styles/loginPage.module.css";

const LoginPage = () => {
  return (
    <DefaultOverlay title={"Login"} withScrolling={false}>
      <div className={styles.container}>
        <LoginForm />
      </div>
    </DefaultOverlay>
  );
};

export default LoginPage;
