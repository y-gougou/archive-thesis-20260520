"""Main entry point for 4CH-Current host application."""

import logging
import sys

from PySide6.QtWidgets import QApplication

from .gui import MainWindow


def setup_logging() -> None:
    """Configure application logging."""
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",
        handlers=[logging.StreamHandler(sys.stdout)],
    )


def main() -> None:
    """Main application entry point."""
    setup_logging()

    app = QApplication(sys.argv)
    app.setApplicationName("4CH-Current")
    app.setOrganizationName("4CH-Current Team")

    window = MainWindow()
    window.show()

    sys.exit(app.exec())


if __name__ == "__main__":
    main()
