import { useParams } from "react-router";
import MockContainer from "./mockContainer";
import DefaultOverlay from "../../overlay/overlay";

const Page: React.FC = () => {
  const { name } = useParams<{ name: string }>();

  return (
    <DefaultOverlay title={name}>
      <MockContainer name={name} />
    </DefaultOverlay>
  );
};

export default Page;
