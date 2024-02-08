interface ContainerProps {
  name: string;
}

const MockContainer: React.FC<ContainerProps> = ({ name }) => {
  return (
    <>
      <strong>{name}</strong>
      <p>
        Explore{" "}
        <a
          target="_blank"
          rel="noopener noreferrer"
          href="https://ionicframework.com/docs/components"
        >
          UI Components
        </a>
      </p>
    </>
  );
};

export default MockContainer;
